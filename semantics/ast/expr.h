/* An expression is a combination of values and operations 
that is evaluated according to specific rules and yields a
value such as an integer, floating point, or string */

#ifndef EXPR_H
#define EXPR_H

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
	struct symbol *symbol;
};

#endif