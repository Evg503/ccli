#include "unity.h"
#include "func_list.h"
#include <debug_malloc.h>   


void setUp(void) {
}

void tearDown(void) {
    print_malloc_stats();
}
int add(int a, int b) {
    return a+b;
}

REG_FUNCTION(test_add_numbers) {
    int result = add(2, 3);
    TEST_ASSERT_EQUAL(5, result);
}

int main(void) {
    UNITY_BEGIN();

    RUN_ALL_TESTS();
    
    return UNITY_END();
}
