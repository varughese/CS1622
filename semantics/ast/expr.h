typedef enum {
	EXPR_ADD,
	EXPR_SUB,
	EXPR_MUL,
	EXPR_DIV,
	EXPR_ASSIGN,
	EXPR_SUBSCRIPT,
	EXPR_CALL,
	EXPR_ARG,
	EXPR_NAME,
	EXPR_LE,
	EXPR_LT,
	EXPR_GT,
	EXPR_GE,
	EXPR_ISEQ,
	EXPR_NEQ,
	EXPR_SEMICOLON,
	EXPR_INTEGER_LITERAL,
	EXPR_STRING_LITERAL
} expr_t;

struct expr {
	expr_t kind;
	struct expr *left;
	struct expr *right;
	const char *name;
	int integer_value;
	const char * string_literal;
};