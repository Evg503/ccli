#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <Lexer.h>
#include <debug_malloc.h>

#include "Lexer.inc"

static char * read_number(Lexer* lexer) {
    int start = lexer->pos;
    while (isdigit(lexer->source[lexer->pos]))
        lexer->pos++;
    
    int len = lexer->pos - start;
    char* num = (char*)malloc(len + 1);
    strncpy(num, lexer->source + start, len);
    num[len] = '\0';
    
    //lexer->col += len;
    return num;
}

static char* read_identifier(Lexer* lexer) {
    int start = lexer->pos;
    while (isalnum(lexer->source[lexer->pos]) || lexer->source[lexer->pos] == '_')
        lexer->pos++;
    
    int len = lexer->pos - start;
    char* id = (char*)malloc(len + 1);
    strncpy(id, lexer->source + start, len);
    id[len] = '\0';
    
    //lexer->col += len;
    return id;
}
/**
 * Парсит строку в двойных кавычках, начиная с текущей позиции лексера
 * 
 * @param lexer Указатель на лексер, source[pos] должна быть '"'
 * @return Новую строку с распарсенными escape-последовательностями или NULL при ошибке
 *         Вызывающий отвечает за освобождение памяти через free()
 */
static char* read_quoted_string(Lexer* lexer) {
    if (!lexer || !lexer->source || lexer->source[lexer->pos] != '"') {
        return NULL;  // Текущий символ должен быть двойной кавычкой
    }
    
    lexer->pos++;  // Пропускаем открывающую кавычку
    lexer->column++;
    
    size_t capacity = 64;       // Начальная вместимость
    size_t len = 0;
    
    char* result = (char*)malloc(capacity + 1);  // +1 для null-terminator
    if (!result) {
        return NULL;
    }
    
    while (lexer->source[lexer->pos] && lexer->source[lexer->pos] != '"') {
        if (lexer->source[lexer->pos] == '\\') {
            lexer->pos++;  // Пропускаем backslash
            lexer->column++;
            
            if (!lexer->source[lexer->pos]) {
                // Неожиданный конец строки
                free(result);
                return NULL;
            }
            
            char escaped_char;
            switch (lexer->source[lexer->pos]) {
                case 'n':  escaped_char = '\n'; break;
                case 't':  escaped_char = '\t'; break;
                case 'r':  escaped_char = '\r'; break;
                case 'b':  escaped_char = '\b'; break;
                case 'f':  escaped_char = '\f'; break;
                case 'v':  escaped_char = '\v'; break;
                case 'a':  escaped_char = '\a'; break;
                case '\\': escaped_char = '\\'; break;
                case '"':  escaped_char = '"';  break;
                case '\'': escaped_char = '\''; break;
                case '?':  escaped_char = '?';  break;
                
                case 'x': {  // Шестнадцатеричная escape-последовательность
                    lexer->pos++;
                    lexer->column++;
                    
                    if (!isxdigit(lexer->source[lexer->pos])) {
                        free(result);
                        return NULL;  // Ожидается hex-цифра
                    }
                    
                    char hex[3] = {lexer->source[lexer->pos], 0, 0};
                    int hex_len = 1;
                    
                    if (isxdigit(lexer->source[lexer->pos + 1])) {
                        lexer->pos++;
                        lexer->column++;
                        hex[hex_len++] = lexer->source[lexer->pos];
                    }
                    escaped_char = (char)strtol(hex, NULL, 16);
                    break;
                }
                
                case '0': case '1': case '2': case '3':
                case '4': case '5': case '6': case '7': {  // Восьмеричная
                    char oct[4] = {lexer->source[lexer->pos], 0, 0, 0};
                    int oct_len = 1;
                    
                    if (lexer->source[lexer->pos + 1] >= '0' && 
                        lexer->source[lexer->pos + 1] <= '7') {
                        lexer->pos++;
                        lexer->column++;
                        oct[oct_len++] = lexer->source[lexer->pos];
                        
                        if (lexer->source[lexer->pos + 1] >= '0' && 
                            lexer->source[lexer->pos + 1] <= '7') {
                            lexer->pos++;
                            lexer->column++;
                            oct[oct_len++] = lexer->source[lexer->pos];
                        }
                    }
                    escaped_char = (char)strtol(oct, NULL, 8);
                    break;
                }
                
                default:
                    // Если escape-последовательность не распознана,
                    // просто копируем backslash и символ
                    if (len + 2 >= capacity) {
                        capacity *= 2;
                        char* new_result = (char*)realloc(result, capacity + 1);
                        if (!new_result) {
                            free(result);
                            return NULL;
                        }
                        result = new_result;
                    }
                    result[len++] = '\\';
                    result[len++] = lexer->source[lexer->pos];
                    lexer->pos++;
                    lexer->column++;
                    continue;
            }
            
            lexer->pos++;
            lexer->column++;
            
            if (len + 1 >= capacity) {
                capacity *= 2;
                char* new_result = (char*)realloc(result, capacity + 1);
                if (!new_result) {
                    free(result);
                    return NULL;
                }
                result = new_result;
            }
            result[len++] = escaped_char;
        } else {
            // Обычный символ
            if (len + 1 >= capacity) {
                capacity *= 2;
                char* new_result = (char*)realloc(result, capacity + 1);
                if (!new_result) {
                    free(result);
                    return NULL;
                }
                result = new_result;
            }
            
            // Обработка перевода строки в исходном коде
            if (lexer->source[lexer->pos] == '\n') {
                lexer->line++;
                lexer->column = 0;
            }
            
            result[len++] = lexer->source[lexer->pos];
            lexer->pos++;
            lexer->column++;
        }
    }
    
    if (lexer->source[lexer->pos] != '"') {
        // Закрывающая кавычка не найдена
        free(result);
        return NULL;
    }
    
    // Пропускаем закрывающую кавычку
    lexer->pos++;
    lexer->column++;
    
    // Добавляем null-terminator
    result[len] = '\0';

    return result;
}

Lexer* create_Lexer() {
    Lexer* lex;
    lex = malloc(sizeof(Lexer));
    if(lex) {
        lex->source = NULL;
        lex->include = NULL;
        lex->next = NULL;
        lex->pos = 0;
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

Token* get_next_token(Lexer* lexer)
{
    Token* token;
    token = init_Token();

    char c = (lexer && lexer->source)?lexer->source[lexer->pos]:0;

    // skip whitespace and comment
    while(c && (isspace(c) || c == '/')){
        if(c == '/')
        {
            if(lexer->source[lexer->pos+1] == '/')
            { // skip for /n or /eof
                while(c && c !='\n' && c !='\r')
                {
                    c = lexer->source[++lexer->pos];
                }
            } else if(lexer->source[lexer->pos+1] == '/')
            { //skip for */ or /eof
                bool is_star = false;
                while(c && !(is_star && c == '/'))
                {
                    is_star = c == '*';
                    c = lexer->source[++lexer->pos];
                }
            } else
            { // division?
                break;
            }
        }
        c = lexer->source[++lexer->pos];
    }
    if (c == '\0') {
        token->type = TOKEN_EOF;
        return token;
    }
    if (isdigit(c)) {
        token->value = read_number(lexer);
        token->type = TOKEN_NUMBER;
        return token;
    }
    if (isalpha(c) || c == '_') {
        token->value = read_identifier(lexer);
        token->type = TOKEN_IDENTIFIER;
        for(int i = 0; keywords[i].id != TOKEN_EOF; ++i)
        {
            if(strcmp(token->value, keywords[i].str) == 0)
            {
                token->type = keywords[i].id;
                break;
            }
        }
        return token;
    }
        // Строки
    if (c == '"') {
        token->value = read_quoted_string(lexer);
        if(token->value)
            token->type = TOKEN_STRING;
        else
            ; //error
        return token;
    }

    return token;
}

Token* init_Token() {
    Token * token = malloc(sizeof * token);
    memset(token, 0, sizeof(Token));
    return  token;
}

void free_Token(Token** token) {
    free((*token)->value);
    free(*token);
    *token = NULL;

}

/*
+ 
+= 
++ 
- 
-= 
-- 
-> 
->* 
* 
*= 
/ 
/= 
% 
%= 
^ 
^= 
& 
&= 
&& 
| 
|= 
|| 
~ 
! 
!= 
= 
== 
< 
<= 
<< 
<<= 
<=> 
> 
>= 
>> 
>>= 
, 
(
) 
[
]

*/