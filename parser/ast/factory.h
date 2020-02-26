#ifndef MATMING_FACTORY
#define MATMING_FACTORY

struct decl {
	char *name;
	struct type *type; 
	struct expr *value;
	struct stmt *code;
	struct decl *next;
};

struct decl *create_decl(
	char *name,
	struct type *type,
	struct expr *value,
	struct stmt *code,
	struct decl *next
);

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

struct expr *create_expr(expr_t kind, struct expr *L, struct expr *R );
struct expr *expr_create_name( const char *name );
struct expr *expr_create_integer_literal(int i);

/*
The body of a function consists of a sequence of statements. A statement
indicates that the program is to take a particular action in 
the order specified, such as computing a value, performing a loop, 
or choosing between branches of an alternative. A statement can 
also be a declaration of a local variable. Here is the stmt structure:
*/

typedef enum {
	STMT_DECL,
	STMT_COMPOUND,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_ITERATION,
	STMT_RETURN,
	STMT_BLOCK
} stmt_t;

struct stmt {
	stmt_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};

struct stmt *create_stmt(
	stmt_t kind,
	struct decl *decl, 
	struct expr *init_expr,
	struct expr *expr, 
	struct expr *next_expr,
	struct stmt *body, 
	struct stmt *else_body,
	struct stmt *next
);

struct stmt *stmt_create_compound_stmt(struct stmt *local_declarations, struct stmt *statement_list);
struct stmt *stmt_create_return(struct expr *expr);
struct stmt *stmt_create_if_else(struct expr *condition, struct stmt *if_body, struct stmt *else_body);
struct stmt *stmt_create_expr(struct expr *expr);
struct stmt *stmt_create_iteration(struct expr *condition, struct stmt *body);
struct stmt *stmt_create_semicolon();

typedef enum {
	TYPE_VOID,
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION
} type_t;

struct type {
	type_t kind;
	struct type *subtype;
	struct param_list *params;
};

struct param_list {
	char *name;
	struct type *type;
	struct param_list *next;
};

struct type *create_type(
	type_t kind,
	struct type *subtype,
	struct param_list *params
);

struct param_list *create_param_list(
	char *name,
	struct type *type,
	struct param_list *next
);

#endif