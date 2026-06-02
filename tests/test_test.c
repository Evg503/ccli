#include "unity.h"
#include "func_list.h"

#include <debug_malloc.h>

int add(int a, int b) {
    return a+b;
}

void setUp(void) {
}

void tearDown(void) {
    print_malloc_stats();
}

REG_FUNCTION(test_add_numbers) {
    int result = add(2, 3);
    TEST_ASSERT_EQUAL(5, result);
}

REG_FUNCTION(test_malloc) {
    void *p = malloc(42);
    TEST_ASSERT_FALSE(check_allocs());
    free(p);
    TEST_ASSERT_TRUE(check_allocs());
    p = malloc(24);
    TEST_ASSERT_FALSE(check_allocs());
    free(p);
    TEST_ASSERT_TRUE(check_allocs());
}

REG_FUNCTION(test_malloc2) {
    void *p1 = malloc(10);
    void *p2 = malloc(100);
    void *p3 = malloc(1000);
    void *p4 = malloc(10000);
    void *p5 = malloc(100000);
    void *p6 = malloc(1000000);
    TEST_ASSERT_FALSE(check_allocs());
    print_malloc_stats();
    free(p1);
    free(p3);
    free(p5);
    free(p6);
    free(p4);
    free(p2);
    TEST_ASSERT_TRUE(check_allocs());
}
REG_FUNCTION(test_realloc) {
    size_t capacity = 10;
    char *p1 = malloc(capacity);
    for(size_t i = 0; i < 256; ++i)
    {
        while (i>=capacity){
            capacity*=2;
            p1 = realloc(p1, capacity);
        }
        p1[i]=(char)i;
    }
    for(size_t i = 0; i < 256; ++i)
    {
        TEST_ASSERT(p1[i] == (char)i);
    }
    free(p1);
    print_malloc_stats();
    TEST_ASSERT_TRUE(check_allocs());
}

REG_FUNCTION(test_strdup) {
    char *str = strdup("Some const string");
    TEST_ASSERT_FALSE(check_allocs());
    free(str);
    TEST_ASSERT_TRUE(check_allocs());
}
// Регистрируем и сразу пишем тело (работает в любых .c файлах проекта)
REG_FUNCTION(print_apple) {
    printf("Apple\n");
    char *str = strdup("Some const string");
    TEST_ASSERT_FALSE(check_allocs());
    free(str);
    TEST_ASSERT_TRUE(check_allocs());
}

REG_FUNCTION(print_banana) {
    printf("Banana\n");
    char *str = strdup("Some const string");
    TEST_ASSERT_FALSE(check_allocs());
    free(str);
    TEST_ASSERT_TRUE(check_allocs());
}

REG_FUNCTION(print_cherry) {
    printf("Cherry\n");
    char *str = strdup("Some const string");
    TEST_ASSERT_FALSE(check_allocs());
    free(str);
    TEST_ASSERT_TRUE(check_allocs());
}

int main(void) {
    UNITY_BEGIN();

    RUN_ALL_TESTS();
        //     test_case_t* func_array = NULL; 
        // /* Кроссплатформенно получаем указатель на начало массива и его размер */
        // size_t total = get_registered_functions(&func_array); 
        
        // printf("Найдено функций во время компиляции: %zu\n\n", total); 
        // \
        // /* Перебираем массив*/ 
        // for (size_t i = 0; i < total; i++) { 
        //     /* Из-за особенностей выравнивания MSVC, между маркерами могут быть NULL-указатели*/ 
        //     if (func_array[i].fn != NULL) { 
        //         printf("Running test(%d): %s\n", (int)i, func_array[i].name);   
        //         UnityDefaultTestRun(func_array[i].fn, func_array[i].name  , __LINE__); 
        //     } 
        // } 


    return UNITY_END();
}
