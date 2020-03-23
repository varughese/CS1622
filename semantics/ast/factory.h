#ifndef MATMING_FACTORY
#define MATMING_FACTORY

#include "type.h"
#include "stmt.h"
#include "decl.h"
#include "expr.h"

/************* TYPE ***************/

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

/************* DECL ***************/

struct decl *create_decl(
	char *name,
	struct type *type,
	int array_size,
	struct stmt *code,
	struct decl *next
);

struct decl *create_function_declaration(
	char *name, 
	struct type *return_type,
	struct param_list *params,
	struct stmt *code
);

struct decl *create_var_declaration(
	char *name, 
	struct type *type
);

struct decl *create_array_var_declaration(
	char *name, 
	struct type *type,
	int array_size
);

/************* EXPR ***************/

struct expr *create_expr(expr_t kind, struct expr *L, struct expr *R );
struct expr *expr_create_name( const char *name );
struct expr *expr_create_integer_literal(int i);

/************* STMT ***************/

struct stmt *create_stmt(stmt_t kind,
	struct decl *decl, struct expr *expr,
	struct stmt *body, struct stmt *else_body,
	struct stmt *next
);

struct stmt *stmt_create_compound_stmt(struct decl *local_declarations, struct stmt *statement_list);
struct stmt *stmt_create_return(struct expr *expr);
struct stmt *stmt_create_if_else(struct expr *condition, struct stmt *if_body, struct stmt *else_body);
struct stmt *stmt_create_expr(struct expr *expr);
struct stmt *stmt_create_iteration(struct expr *condition, struct stmt *body);
struct stmt *stmt_create_semicolon();

#endif