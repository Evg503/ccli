
static struct Keywords {
    TokenType id;
    const char* str;
} keywords[] = {
{TOKEN_AUTO, "auto"},
{TOKEN_BREAK, "break"},
{TOKEN_CASE, "case"},
{TOKEN_CHAR, "char"},
{TOKEN_CONST, "const"},
{TOKEN_CONTINUE, "continue"},
{TOKEN_DEFAULT, "default"},
{TOKEN_DO, "do"},
{TOKEN_DOUBLE, "double"},
{TOKEN_ELSE, "else"},
{TOKEN_ENUM, "enum"},
{TOKEN_EXTERN, "extern"},
{TOKEN_FLOAT, "float"},
{TOKEN_FOR, "for"},
{TOKEN_GOTO, "goto"},
{TOKEN_IF, "if"},
{TOKEN_INLINE, "inline"},
{TOKEN_INT, "int"},
{TOKEN_LONG, "long"},
{TOKEN_REGISTER, "register"},
{TOKEN_RESTRICT, "restrict"},
{TOKEN_RETURN, "return"},
{TOKEN_SHORT, "short"},
{TOKEN_SIGNED, "signed"},
{TOKEN_SIZEOF, "sizeof"},
{TOKEN_STATIC, "static"},
{TOKEN_STRUCT, "struct"},
{TOKEN_SWITCH, "switch"},
{TOKEN_TYPEDEF, "typedef"},
{TOKEN_UNION, "union"},
{TOKEN_UNSIGNED, "unsigned"},
{TOKEN_VOID, "void"},
{TOKEN_VOLATILE, "volatile"},
{TOKEN_WHILE, "while"},

// Ключевые слова из C99 / C11 / C23
{TOKEN_BOOL, "_Bool"},
{TOKEN_COMPLEX, "_Complex"},
{TOKEN_IMAGINARY, "_Imaginary"},
{TOKEN_ALIGNAS, "_Alignas"},
{TOKEN_ALIGNOF, "_Alignof"},
{TOKEN_ATOMIC, "_Atomic"},
{TOKEN_GENERIC, "_Generic"},
{TOKEN_NORETURN, "_Noreturn"},
{TOKEN_STATIC_ASSERT, "_Static_assert"},
{TOKEN_THREAD_LOCAL, "_Thread_local"},

// Современные альтернативы из стандарта C23
{TOKEN_ALIGNOF_ALT, "alignof"},
{TOKEN_ALIGNAS_ALT, "alignas"},
{TOKEN_BOOL_ALT, "bool"},
{TOKEN_TRUE, "true"},
{TOKEN_FALSE, "false"},
{TOKEN_STATIC_ASSERT_ALT, "static_assert"},
{TOKEN_THREAD_LOCAL_ALT, "thread_local"},
{TOKEN_TYPEOF, "typeof"},
{TOKEN_TYPEOF_UNQUAL, "typeof_unqual"},
{TOKEN_NULLPTR, "nullptr"},
{TOKEN_EOF, NULL}
};

typedef struct Operators {
    TokenType token;
    struct Operators *next;
} Operators;


