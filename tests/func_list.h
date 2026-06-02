#pragma once
#include <stddef.h>

// Определение типа функции
typedef void (*action_fn)(void);
typedef struct {
    const char* name;
    const action_fn fn;
} test_case_t;

// === РЕАЛИЗАЦИЯ ДЛЯ WINDOWS (MSVC, Clang-cl, lld-link) ===
#if defined(_WIN32) || defined(_WIN64)

    // Принудительно отключаем предупреждения Clang на неизвестные прагмы MSVC, если они будут
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunknown-pragmas"
    #endif


    // В Clang-cl для распределения по секциям используется атрибут __section__, а не __declspec(allocate)
    #ifdef __clang__
        __attribute__((section("mysec$A"), used)) __declspec(selectany) test_case_t __start_my_list = { NULL };
        __attribute__((section("mysec$Z"), used)) __declspec(selectany) test_case_t __stop_my_list = { NULL };

        #define REG_FUNCTION(name) \
            void name(void); \
            __attribute__((section("mysec$I"), used)) static test_case_t __stored_ptr_##name = {#name, name }  ; \
            void name(void)

        static inline size_t get_registered_functions(test_case_t** start) {
            *start = (test_case_t*)(&__start_my_list)+1; // Пропускаем маркер NULL
            return (size_t)((test_case_t*)(&__stop_my_list) - (*start));
        }

    #else
         //1. Объявляем секции для Windows-линкера
         #pragma section("mysec$A", read)
         #pragma section("mysec$I", read)
         #pragma section("mysec$Z", read)
        // Родной синтаксис для чистого MSVC (cl.exe)
        __declspec(allocate("mysec$A")) __declspec(selectany) test_case_t __start_my_list = { NULL };
        __declspec(allocate("mysec$Z")) __declspec(selectany) test_case_t __stop_my_list = { NULL };

        #define REG_FUNCTION(name) \
            void name(void); \
            __declspec(allocate("mysec$I")) static test_case_t __stored_ptr_##name ={#name, name }; \
            void name(void)

        static inline size_t get_registered_functions(test_case_t** start) {
            void** p = &__start_my_list;
            while (*p == NULL) ++p; // Пропускаем маркер NULL
            *start = (test_case_t*)(p); 
            return (size_t)((test_case_t*)(&__stop_my_list) - (*start));
        }
#endif


    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif

// === РЕАЛИЗАЦИЯ ДЛЯ LINUX / MACOS (GCC / Нативный Clang) ===
#else

    extern test_case_t __start_my_list_sec[];
    extern test_case_t __stop_my_list_sec[];

    #define REG_FUNCTION(name) \
        void name(void); \
        __attribute__((section("my_list_sec"), used)) \
        static test_case_t __stored_ptr_##name ={  name, #name }; \
        void name(void)

    static inline size_t get_registered_functions(test_case_t** start) {
        *start = __start_my_list_sec;
        return (size_t)(__stop_my_list_sec - __start_my_list_sec);
    }

#endif

