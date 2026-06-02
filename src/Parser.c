#include "Parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <debug_malloc.h>



Parser* create_Parser(Lexer* lexer) {
    Parser* parser = malloc(sizeof(Parser));
    if(parser) {
        parser->lexer = lexer;
        parser->current_token = NULL;
    }
    return parser;
}

void free_Parser(Parser** parser) {
    if(*parser) {
        free_Token(&(*parser)->current_token);
        free_Lexer(&(*parser)->lexer);
        free(*parser);
        *parser = NULL;
    }
}

void free_ASTNode(ASTNode** node) {
    if (*node) {
        switch ((*node)->type) {
            case NODE_IDENTIFIER:
                free((*node)->identifier);
                break;
            case NODE_UNARY_OP:
                free((*node)->unary_op.operator);
                free_ASTNode(&(*node)->unary_op.operand);
                break;
            case NODE_BINARY_OP:
                free_ASTNode(&(*node)->binary_op.left);
                free_ASTNode(&(*node)->binary_op.right);
                break;
            case NODE_IF_STMT:
                free_ASTNode(&(*node)->if_stmt.condition);
                free_ASTNode(&(*node)->if_stmt.true_branch);
                free_ASTNode(&(*node)->if_stmt.false_branch);
                break;
            case NODE_FUNCTION_CALL:
                free((*node)->function_call.function_name);
                for (size_t i = 0; i < (*node)->function_call.arg_count; i++) {
                    free_ASTNode(&(*node)->function_call.arguments[i]);
                }
                free((*node)->function_call.arguments);
                break;
            case NODE_ASSIGNMENT:
                free((*node)->assignment.variable_name);
                free_ASTNode(&(*node)->assignment.value);
                break;
            default:
                break;
        }
        free(*node);
        *node = NULL;
    }
}
void print_ASTNode(const ASTNode* node, int indent_level) {
    if (!node) return;

    for (int i = 0; i < indent_level; i++) {
        printf("  ");
    }

    switch (node->type) {
        case NODE_IDENTIFIER:
            printf("Identifier: %s\n", node->identifier);
            break;
        case NODE_NUMBER:
            printf("Number: %d\n", node->number);
            break;
        case NODE_UNARY_OP:
            printf("Unary Operator: %s\n", node->unary_op.operator);
            print_ASTNode(node->unary_op.operand, indent_level + 1);
            break;
        case NODE_BINARY_OP:
            printf("Binary Operator:\n");
            print_ASTNode(node->binary_op.left, indent_level + 1);
            print_ASTNode(node->binary_op.right, indent_level + 1);
            break;
        case NODE_IF_STMT:
            printf("If Statement:\n");
            print_ASTNode(node->if_stmt.condition, indent_level + 1);
            printf("True Branch:\n");
            print_ASTNode(node->if_stmt.true_branch, indent_level + 1);
            printf("False Branch:\n");
            print_ASTNode(node->if_stmt.false_branch, indent_level + 1);
            break;
        case NODE_FUNCTION_CALL:
            printf("Function Call: %s\n", node->function_call.function_name);
            for (size_t i = 0; i < node->function_call.arg_count; i++) {
                print_ASTNode(node->function_call.arguments[i], indent_level + 1);
            }
            break;
        case NODE_ASSIGNMENT:
            printf("Assignment: %s\n", node->assignment.variable_name);
            print_ASTNode(node->assignment.value, indent_level + 1);
            break;
        default:
            printf("Unknown Node Type\n");
    }
}

ASTNode* create_ASTNode() {
    ASTNode* node = malloc(sizeof(ASTNode));
    if (node) {
        memset(node, 0, sizeof(ASTNode));
        node->type = NODE_UNKNOWN;
    }
    return node;
}

// void free_ASTNodeArray(ASTNode*** array, size_t count) {
//     if (array && *array) {
//         for (size_t i = 0; i < count; i++) {
//             free_ASTNode(&(*array)[i]);
//         }
//         free(*array);
//         *array = NULL;
//     }
// }

ASTNode* parse_program(Parser* parser){
    ASTNode* node = create_ASTNode();
    while((parser->current_token = get_next_token(parser->lexer))==TOKEN_EOF)    {
    }
    return node;
}
ASTNode* parse_statement(Parser* parser){
    // Здесь будет логика для парсинга одного оператора
    // Например, можно парсить выражение и ожидать точку с запятой
    return parse_expression(parser);
}
ASTNode* parse_expression(Parser* parser){
    // Здесь будет логика для парсинга выражения
    // Например, можно парсить идентификатор, оператор и другое выражение
    return NULL;

}

