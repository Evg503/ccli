#include "unity.h"

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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_numbers);
    return UNITY_END();
}
