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

void test_Lexer_Character(void) {
    Lexer *lex = NULL;
    lex = create_Lexer_from_String("'a' '\a' '\\n' '\\\\' '\\\"' '\\\'' '\042' '\xff'" );
    for(char *expected = "a\a\n\\\"\'\042\xff"; expected[0]; expected++) {
        char buf[128];
        sprintf(buf, "Testing character: '%c' (0x%02x)\n", expected[0], (unsigned char)expected[0]);
        Token *t1 = get_next_token(lex);
        UNITY_TEST_ASSERT(t1->type == TOKEN_CHARACTER, __LINE__, buf);
        UNITY_TEST_ASSERT_EQUAL_CHAR(t1->value[0], expected[0], __LINE__, buf);
        UNITY_TEST_ASSERT_EQUAL_CHAR(t1->value[1], '\0', __LINE__, buf);
        free_Token(&t1);
        UNITY_TEST_ASSERT_NULL(t1, __LINE__, buf);
    }
    Token *t2 = get_next_token(lex);
    TEST_ASSERT(t2->type == TOKEN_EOF);
    free_Token(&t2);
    free_Lexer(&lex);
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
    TEST_ASSERT(t1->type == TOKEN_STRING);
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
void test_Complex_Lexer(void) {
    Lexer *lex = NULL;
    lex = create_Lexer_from_String("//My best program\nint main()\n{return /*0 is true in bash\n but not in C */0;}");
    Token* t[10];
    for(int i=0; i<10; i++){
        t[i] = get_next_token(lex);
    }

    TEST_ASSERT(t[0]->type == TOKEN_INT);
    TEST_ASSERT_EQUAL_STRING(t[0]->value,"int");
    TEST_ASSERT(t[1]->type == TOKEN_IDENTIFIER);
    TEST_ASSERT_EQUAL_STRING(t[1]->value,"main");
    TEST_ASSERT(t[2]->type == TOKEN_LPAREN);
    TEST_ASSERT(t[3]->type == TOKEN_RPAREN);  
    TEST_ASSERT(t[4]->type == TOKEN_LBRACE);
    TEST_ASSERT(t[5]->type == TOKEN_RETURN);
    TEST_ASSERT(t[6]->type == TOKEN_NUMBER);
    TEST_ASSERT_EQUAL_STRING(t[6]->value,"0");
    TEST_ASSERT(t[7]->type == TOKEN_SEMICOLON);
    TEST_ASSERT(t[8]->type == TOKEN_RBRACE);
    TEST_ASSERT(t[9]->type == TOKEN_EOF);

    for(int i=0; i<10; i++){
        free_Token(&t[i]);
        TEST_ASSERT_NULL(t[i]);
    }

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
    RUN_TEST(test_Lexer_Character);
    RUN_TEST(test_Lexer_String);
    RUN_TEST(test_Complex_Lexer);
    print_malloc_stats();
    return UNITY_END();
}
