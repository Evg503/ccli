#include "unity.h"
#include <debug_malloc.h>

int add(int a, int b) {
    return a+b;
}

void setUp(void) {
}

void tearDown(void) {
}

void test_add_numbers(void) {
    int result = add(2, 3);
    TEST_ASSERT_EQUAL(5, result);
}

void test_malloc() {
    void *p = malloc(42);
    TEST_ASSERT_FALSE(check_allocs());
    free(p);
    TEST_ASSERT_TRUE(check_allocs());
}

void test_strdup() {
    char *str = strdup("Some const string");
    TEST_ASSERT_FALSE(check_allocs());
    free(str);
    TEST_ASSERT_TRUE(check_allocs());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_numbers);
    RUN_TEST(test_malloc);
    RUN_TEST(test_strdup);
    print_malloc_stats();
    return UNITY_END();
}
