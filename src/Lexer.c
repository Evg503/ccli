#include <stdlib.h>
#include <Lexer.h>

Lexer* create_Lexer() {
    Lexer* lex;
    lex = malloc(sizeof(Lexer));
    if(lex) {
        lex->include = NULL;
        lex->next = NULL;
    }
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
