#ifndef tokens
#define tokens

typedef enum token{
	TOKEN_EOF=0,
	TOKEN_ID,
	TOKEN_NUM,
	TOKEN_KEY,
	TOKEN_SYM,
	TOKEN_ERROR_UNCLOSED_COMMENT,
	TOKEN_ERROR,
} token;

static inline char *tokenToString(enum token tok)
{
    static const char *strings[] = { "EOF", "ID", "NUM", "KEY", "SYM", "ERROR", "ERROR" };

    return (unsigned char *) strings[tok];
}

#endif
