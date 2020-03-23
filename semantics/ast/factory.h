#ifndef MATMING_FACTORY
#define MATMING_FACTORY

#include "type.h"
#include "stmt.h"
#include "decl.h"
#include "expr.h"

/* A type structure encodes the type of every variable and function 
mentioned in a declaration. Primitive types like integer and boolean 
are expressed by simply setting the kind field appropriately, and leaving the
other fields null. Compound types like array and function are built by
connecting multiple type structures together. */

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