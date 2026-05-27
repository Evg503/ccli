#include <Lexer.h>

#include "unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_Lexer(void) {
   Lexer *lex;
   lex = create_Lexer();
   TEST_ASSERT_NULL(lex->include);
   TEST_ASSERT_NULL(lex->next);
   free_Lexer(&lex);
   TEST_ASSERT_NULL(lex);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Lexer);
    return UNITY_END();
}
