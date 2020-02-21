typedef enum {
	STMT_DECL,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_FOR,
	STMT_RETURN,
	STMT_BLOCK
} stmt_t;

/*
The body of a function consists of a sequence of statements. A statement
indicates that the program is to take a particular action in 
the order specified, such as computing a value, performing a loop, 
or choosing between branches of an alternative. A statement can 
also be a declaration of a local variable. Here is the stmt structure:
*/

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


struct stmt *create_stmt(stmt_t kind,
	struct decl *decl, struct expr *init_expr,
	struct expr *expr, struct expr *next_expr,
	struct stmt *body, struct stmt *else_body,
	struct stmt *next
) {
	struct stmt *s = malloc(sizeof(*s));
	s->kind = kind;
	s->decl = decl;
	s->init_expr = init_expr;
	s->expr = expr;
	s->next_expr = next_expr;
	s->body = body;
	s->else_body = else_body;
	s->next = next;
	return s;

};