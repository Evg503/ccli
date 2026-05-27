#include <Lexer.h>

#include "unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_Lexer(void) {
   Lexer *lex = NULL;
   lex = create_Lexer_from_String("");
   TEST_ASSERT_NOT_NULL(lex->source);
   
   free_Lexer(&lex);
   TEST_ASSERT_NULL(lex);
}
void test_Empty_Lexer(void) {
   Lexer *lex;
   lex = create_Lexer();
   TEST_ASSERT_NULL(lex->source);
   TEST_ASSERT_NULL(lex->include);
   TEST_ASSERT_NULL(lex->next);
   free_Lexer(&lex);
   TEST_ASSERT_NULL(lex);
}

void print_malloc_stats();
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Lexer);
    RUN_TEST(test_Empty_Lexer);
    print_malloc_stats();
    return UNITY_END();
}
