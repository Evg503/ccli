#pragma once


typedef struct Lexer{
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
