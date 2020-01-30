#ifndef tokens
#define tokens

enum token{
	TOKEN_EOF=0,
	TOKEN_ID,
	TOKEN_NUM,
	TOKEN_KEY,
	TOKEN_SYM,
	ERROR_UNCLOSED_COMMENT,
	ERROR_INVALID_CHARACTER,
};

static inline char is_error_token(enum token tok) {
	/* Since token is an enum, defined by ints, we can use integer comparision to test
	   if a token is a error token, since all errors are defined last */
	return tok >= ERROR_UNCLOSED_COMMENT; 
}

static inline char *token_to_string(enum token tok) {
    static const char *strings[] = { "EOF", "ID", "NUM", "KEY", "SYM", "ERROR", "ERROR" };
    return (unsigned char *) strings[tok];
}

#endif
