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
void free_Lexer(Lexer**);
