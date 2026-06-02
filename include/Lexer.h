#pragma once
#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_CHARACTER,
    
    // Операторы
    TOKEN_ASSIGN,       // =
    TOKEN_PLUS,         // +
    TOKEN_MINUS,        // -
    TOKEN_STAR,         // *
    TOKEN_SLASH,        // /
    TOKEN_PERCENT,      // %
    TOKEN_PLUS_PLUS,    // ++
    TOKEN_MINUS_MINUS,  // --
    
    // Сравнение
    TOKEN_EQ,           // ==
    TOKEN_NEQ,          // !=
    TOKEN_LT,           // <
    TOKEN_GT,           // >
    TOKEN_LE,           // <=
    TOKEN_GE,           // >=
    
    // Логические
    TOKEN_AND,          // &&
    TOKEN_OR,           // ||
    TOKEN_NOT,          // !
    
    // Битовые
    TOKEN_BIT_AND,      // &
    TOKEN_BIT_OR,       // |
    TOKEN_BIT_XOR,      // ^
    TOKEN_BIT_NOT,      // ~
    TOKEN_SHIFT_LEFT,   // <<
    TOKEN_SHIFT_RIGHT,  // >>
    
    // Разделители
    TOKEN_SEMICOLON,    // ;
    TOKEN_COMMA,        // ,
    TOKEN_LPAREN,       // (
    TOKEN_RPAREN,       // )
    TOKEN_LBRACE,       // {
    TOKEN_RBRACE,       // }
    TOKEN_LBRACKET,     // [
    TOKEN_RBRACKET,     // ]
    TOKEN_QUESTION,     // ?
    TOKEN_COLON,        // :
    
    // Ключевые слова
    TOKEN_AUTO,
    TOKEN_BREAK,
    TOKEN_CASE,
    TOKEN_CHAR,
    TOKEN_CONST,
    TOKEN_CONTINUE,
    TOKEN_DEFAULT,
    TOKEN_DO,
    TOKEN_DOUBLE,
    TOKEN_ELSE,
    TOKEN_ENUM,
    TOKEN_EXTERN,
    TOKEN_FLOAT,
    TOKEN_FOR,
    TOKEN_GOTO,
    TOKEN_IF,
    TOKEN_INLINE,
    TOKEN_INT,
    TOKEN_LONG,
    TOKEN_REGISTER,
    TOKEN_RESTRICT,
    TOKEN_RETURN,
    TOKEN_SHORT,
    TOKEN_SIGNED,
    TOKEN_SIZEOF,
    TOKEN_STATIC,
    TOKEN_STRUCT,
    TOKEN_SWITCH,
    TOKEN_TYPEDEF,
    TOKEN_UNION,
    TOKEN_UNSIGNED,
    TOKEN_VOID,
    TOKEN_VOLATILE,
    TOKEN_WHILE,
    // Ключевые слова из C99 / C11 / C23
    TOKEN_BOOL,
    TOKEN_COMPLEX,
    TOKEN_IMAGINARY,
    TOKEN_ALIGNAS,
    TOKEN_ALIGNOF,
    TOKEN_ATOMIC,
    TOKEN_GENERIC,
    TOKEN_NORETURN,
    TOKEN_STATIC_ASSERT,
    TOKEN_THREAD_LOCAL,
    // Современные альтернативы из стандарта C23
    TOKEN_ALIGNOF_ALT,
    TOKEN_ALIGNAS_ALT,
    TOKEN_BOOL_ALT,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_STATIC_ASSERT_ALT,
    TOKEN_THREAD_LOCAL_ALT,
    TOKEN_TYPEOF,
    TOKEN_TYPEOF_UNQUAL,
    TOKEN_NULLPTR
} TokenType;

// Структура токена
typedef struct Token {
    TokenType type;
    char* value;
    int line;
    int column;
} Token;


typedef struct Lexer {
    const char * source;
    int pos;
    int line;
    int column;
    struct Lexer* include;
    struct Lexer* next;
} Lexer;

Lexer* create_Lexer();
Lexer* create_Lexer_from_String(const char*);
void free_Lexer(Lexer**);

Token* get_next_token(Lexer* lexer);

Token* init_Token();
void free_Token(Token**);

#endif // LEXER_H