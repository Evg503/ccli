#pragma once
#ifndef TEST_FUNC_LIST_H
#define TEST_FUNC_LIST_H   

#include "Lexer.h"

typedef enum NodeType {
    NODE_UNKNOWN,
    NODE_PROGRAM,
    NODE_STATEMENT,
    NODE_EXPRESSION,
    NODE_BLOCK,
    
    NODE_NUMBER,
    NODE_IDENTIFIER,
    NODE_UNARY_OP,
    NODE_BINARY_OP,
    NODE_IF_STMT,
    NODE_FUNCTION_CALL,
    NODE_ASSIGNMENT
} NodeType;

typedef struct Parser {

    Lexer* lexer;
    Token* current_token;

} Parser;

typedef struct ASTNode {
    // Структура для представления узла абстрактного синтаксического дерева
    // Здесь можно добавить поля для типа узла, значения, детей и т.д.
    NodeType type;
    union {
        // Данные для различных типов узлов
        char* identifier;
        int number;
        struct {
            char* operator;
            struct ASTNode* operand;
        } unary_op;
        struct {
            struct ASTNode* left;
            struct ASTNode* right;
        } binary_op;
        struct {
            struct ASTNode* condition;
            struct ASTNode* true_branch;
            struct ASTNode* false_branch;
        } if_stmt;
        struct {
            char* function_name;
            struct ASTNode** arguments;
            size_t arg_count;
        } function_call;
        struct {
            char* variable_name;
            struct ASTNode* value;
        } assignment;
        struct {
            struct ASTNode** statements;
            size_t statement_count;
        } block;
        struct {
            struct ASTNode** statements;
            size_t statement_count;
        } program;
        struct {
            struct ASTNode* statement;
        } statement;
        struct {
            struct ASTNode* expression;
        } expression;
        

    };
} ASTNode;


Parser* create_Parser(Lexer* lexer);
void free_Parser(Parser** parser);

void free_ASTNode(ASTNode** node);
void print_ASTNode(const ASTNode* node, int indent_level);

ASTNode* parse_program(Parser* parser);
ASTNode* parse_statement(Parser* parser);
ASTNode* parse_expression(Parser* parser);

#endif // TEST_FUNC_LIST_H