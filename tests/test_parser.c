#include "unity.h"
#include "func_list.h"
#include <debug_malloc.h>   

#include <Parser.h>

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

REG_FUNCTION(test_Parser) {
    Lexer *lex = NULL;
    lex = create_Lexer_from_String("12345");
    Parser *parser = create_Parser(lex);
    TEST_ASSERT(parser != NULL);  
    
    free_Parser(&parser);
    TEST_ASSERT_NULL(parser);
}

REG_FUNCTION(test_Parser_Empty) {
    Lexer *lex = create_Lexer();
    Parser *parser = create_Parser(lex);
    TEST_ASSERT(parser != NULL);  
    
    free_Parser(&parser);
    TEST_ASSERT_NULL(parser);
}

REG_FUNCTION(test_Parser_Complex) {
    const char* code = "int main() { return 42; }";
    Lexer *lex = create_Lexer_from_String(code);
    Parser *parser = create_Parser(lex);
    TEST_ASSERT(parser != NULL);  
    
    {
        ASTNode* node = parse_program(parser);
        TEST_ASSERT(node != NULL);
        print_ASTNode(node, 0);
        free_ASTNode(&node);
        TEST_ASSERT_NULL(node);
    }

    free_Parser(&parser);
    TEST_ASSERT_NULL(parser);
}

int main(void) {
    UNITY_BEGIN();

    RUN_ALL_TESTS();
    
    return UNITY_END();
}
