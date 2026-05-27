#include <stdlib.h>
#include <Lexer.h>
#include <debug_malloc.h>

Lexer* create_Lexer() {
    Lexer* lex;
    lex = malloc(sizeof(Lexer));
    if(lex) {
        lex->source = NULL;
        lex->include = NULL;
        lex->next = NULL;
    }
    return lex;
}

Lexer* create_Lexer_from_String(const char* src){
    Lexer* lex = create_Lexer();
    lex->source = src;

    return lex;
}

void free_Lexer(Lexer**lex)
{
    if(*lex) {
        free_Lexer(&(*lex)->next);
        free(*lex);
        *lex = NULL;
    }
}
