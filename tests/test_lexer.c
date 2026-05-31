#include <Lexer.h>
#include <debug_malloc.h>

#include "unity.h"

void setUp(void) {
}

void tearDown(void) {
    if(!check_allocs())
            print_malloc_stats();
    TEST_ASSERT_TRUE(check_allocs());
}

void test_Lexer_Number(void) {
   Lexer *lex = NULL;
   lex = create_Lexer_from_String("12345");
   Token *t1 = get_next_token(lex);
   TEST_ASSERT(t1->type == TOKEN_NUMBER);
   TEST_ASSERT_EQUAL_STRING(t1->value, "12345" );
   Token *t2 = get_next_token(lex);
   TEST_ASSERT(t2->type == TOKEN_EOF);
   free_Token(&t1);
   free_Token(&t2);
   free_Lexer(&lex);
   TEST_ASSERT_NULL(t1);
   TEST_ASSERT_NULL(t2);
   TEST_ASSERT_NULL(lex);
}

void test_Lexer_String(void) {
   Lexer *lex = NULL;
   lex = create_Lexer_from_String("\"Value\"");
   Token *t1 = get_next_token(lex);
   TEST_ASSERT(t1->type == TOKEN_STRING);
   TEST_ASSERT_EQUAL_STRING(t1->value, "Value" );
   Token *t2 = get_next_token(lex);
   TEST_ASSERT(t2->type == TOKEN_EOF);
   free_Token(&t1);
   free_Token(&t2);
   free_Lexer(&lex);
   TEST_ASSERT_NULL(t1);
   TEST_ASSERT_NULL(t2);
   TEST_ASSERT_NULL(lex);
}

void test_Lexer_Spaces(){
   Lexer *lex = NULL;
   lex = create_Lexer_from_String(" \"Value\" ");
   Token *t1 = get_next_token(lex);
   TEST_ASSERT(t1->type != TOKEN_EOF);
   Token *t2 = get_next_token(lex);
   TEST_ASSERT(t2->type == TOKEN_EOF);

   free_Token(&t1);
   free_Token(&t2);
   free_Lexer(&lex);
}

void test_Lexer_Spaces2(){
   Lexer *lex = NULL;
   lex = create_Lexer_from_String("//\n /* Comment\n* -----*/\n\"Value\" ");
   Token *t1 = get_next_token(lex);
   TEST_ASSERT(t1->type != TOKEN_STRING);
   Token *t2 = get_next_token(lex);
   TEST_ASSERT(t2->type == TOKEN_EOF);

   free_Token(&t1);
   free_Token(&t2);
   free_Lexer(&lex);
}

void test_Lexer_Identifier(void) {
   Lexer *lex = NULL;
   lex = create_Lexer_from_String("Identifier");
   Token *t1 = get_next_token(lex);
   TEST_ASSERT(t1->type == TOKEN_IDENTIFIER);
   TEST_ASSERT_EQUAL_STRING(t1->value, "Identifier" );
   Token *t2 = get_next_token(lex);
   TEST_ASSERT(t2->type == TOKEN_EOF);
   free_Token(&t1);
   free_Token(&t2);
   free_Lexer(&lex);
   TEST_ASSERT_NULL(t1);
   TEST_ASSERT_NULL(t2);
   TEST_ASSERT_NULL(lex);
}

void test_Lexer_Keyword(void) {
   Lexer *lex = NULL;
   lex = create_Lexer_from_String("void");
   Token *t1 = get_next_token(lex);
   TEST_ASSERT(t1->type == TOKEN_VOID);
   TEST_ASSERT_EQUAL_STRING(t1->value, "void" );
   Token *t2 = get_next_token(lex);
   TEST_ASSERT(t2->type == TOKEN_EOF);
   free_Token(&t1);
   free_Token(&t2);
   free_Lexer(&lex);
   TEST_ASSERT_NULL(t1);
   TEST_ASSERT_NULL(t2);
   TEST_ASSERT_NULL(lex);
}

void test_Empty_Lexer_String(void) {
   Lexer *lex = NULL;
   lex = create_Lexer_from_String("");
   TEST_ASSERT_NOT_NULL(lex->source);
   Token *t1 = get_next_token(lex);
   TEST_ASSERT(t1->type == TOKEN_EOF);
   Token *t2 = get_next_token(lex);
   TEST_ASSERT(t2->type == TOKEN_EOF);
   free_Token(&t1);
   free_Token(&t2);
   free_Lexer(&lex);
   TEST_ASSERT_NULL(t1);
   TEST_ASSERT_NULL(t2);
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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Empty_Lexer);
    RUN_TEST(test_Empty_Lexer_String);
    RUN_TEST(test_Lexer_Number);
    RUN_TEST(test_Lexer_Identifier);
    RUN_TEST(test_Lexer_Spaces);
    RUN_TEST(test_Lexer_Spaces2);
    RUN_TEST(test_Lexer_Keyword);
    RUN_TEST(test_Lexer_String);
    print_malloc_stats();
    return UNITY_END();
}
