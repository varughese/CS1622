typedef enum {
	STMT_COMPOUND,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_ITERATION,
	STMT_RETURN
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