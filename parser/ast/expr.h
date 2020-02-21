typedef enum {
	EXPR_ADD,
	EXPR_SUB,
	EXPR_MUL,
	EXPR_DIV,
	EXPR_NAME,
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

struct expr *create_expr(expr_t kind, struct expr *L, struct expr *R ) {
	struct expr *e = malloc(sizeof(*e));
	e->kind = kind;
	e->left = L;
	e->right = R;
	e->integer_value = 0;
	e->string_literal = 0;
	e->name = 0;
}

struct expr * expr_create_name( const char *name ) {
	struct expr *e = create_expr(EXPR_NAME, 0,0);
	return e;
};

struct expr * expr_create_integer_literal(int i) {
	struct expr *e = create_expr(EXPR_INTEGER_LITERAL, 0,0);
	e->integer_value = i;
	return e;
};

// struct expr * expr_create_boolean_literal( int b ) {
// 	struct expr *e = create_expr(EXPR_INTEGER_LITERAL, 0,0);
// 	return e;
// };

// struct expr * expr_create_char_literal( char c ) {
// 	struct expr *e = create_expr(EXPR_ADD, 0,0);
// 	return e;
// }

// struct expr * expr_create_string_literal( const char *str ) {
// 	struct expr *e = create_expr(EXPR_ADD, 0,0);
// 	return e;
// }