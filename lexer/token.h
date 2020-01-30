#ifndef tokens
#define tokens

typedef enum token{
	TOKEN_EOF=0,
	TOKEN_ID,
	TOKEN_NUM,
	TOKEN_KEY,
	TOKEN_SYM,
	TOKEN_ERROR_UNCLOSED_COMMENT,
	TOKEN_ERROR_INVALID_CHARACTER,
} token;

static inline char *token_to_string(enum token tok)
{
    static const char *strings[] = { "EOF", "ID", "NUM", "KEY", "SYM", "ERROR", "ERROR" };

    return (unsigned char *) strings[tok];
}

#endif
