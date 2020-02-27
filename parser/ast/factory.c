#include <stdio.h>
#include <stdlib.h>
#include "factory.h"

struct decl *create_decl(
	char *name,
	struct type *type,
	struct expr *value,
	struct stmt *code,
	struct decl *next
) {
	struct decl *d = malloc(sizeof(*d));
	d->name = name;
	d->type = type;
	d->value = value;
	d->code = code;
	d->next = next;
	return d;
}

struct decl *create_function_declaration(
	char *name, 
	struct type *return_type,
	struct param_list *params,
	struct stmt *code
) {
	struct type *fn_type = create_type(TYPE_FUNCTION, return_type, params);
	return create_decl(name, fn_type, 0, code, 0);
}

struct expr *create_expr(expr_t kind, struct expr *L, struct expr *R ) {
	struct expr *e = malloc(sizeof(*e));
	e->kind = kind;
	e->left = L;
	e->right = R;
	e->integer_value = 0;
	e->string_literal = 0;
	e->name = 0;
}

struct expr *expr_create_name( const char *name ) {
	struct expr *e = create_expr(EXPR_NAME, 0,0);
	e->name = name;
	return e;
};

struct expr * expr_create_integer_literal(int i) {
	struct expr *e = create_expr(EXPR_INTEGER_LITERAL, 0,0);
	e->integer_value = i;
	return e;
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

struct stmt *stmt_create_compound_stmt(struct decl *local_declarations, struct stmt *statement_list) {
	// Need to create a cmpd stmt structure or something that 
	// holds the changes ?
	// struct stmt *current_stmt = local_declarations;
	// if(local_declarations != NULL) {
	// 	while(current_stmt->next != NULL) {
	// 		current_stmt = current_stmt->next;
	// 	}
	// 	current_stmt->next = statement_list;
	// } else {
	// 	current_stmt = statement_list;
	// }
	
	struct stmt *cmpd = create_stmt(STMT_COMPOUND, 0, 0, 0, 0, 0, 0, 0);
	cmpd->next = statement_list;
	return cmpd;
}

struct stmt *stmt_create_return(struct expr *expr) {
	return create_stmt(STMT_RETURN, 0, 0, expr, 0, 0, 0, 0);
}

struct stmt *stmt_create_if_else(struct expr *condition, struct stmt *if_body, struct stmt *else_body) {
	return create_stmt(STMT_IF_ELSE, 0, condition, 0, 0, if_body, else_body, 0);
}

struct stmt *stmt_create_expr(struct expr *expr) {
	return create_stmt(STMT_EXPR, 0, 0, expr, 0, 0, 0, 0);
}

struct stmt *stmt_create_iteration(struct expr *condition, struct stmt *body) {
	return create_stmt(STMT_ITERATION, 0, condition, 0, 0, body, 0, 0);
}

struct stmt *stmt_create_semicolon() {
	return create_stmt(STMT_EXPR, 0, create_expr(EXPR_SEMICOLON, 0, 0), 0, 0, 0, 0, 0);
}


struct type *create_type(
	type_t kind,
	struct type *subtype,
	struct param_list *params
) {
	struct type *t = malloc(sizeof(*t));
	t->kind = kind;
	t->subtype = subtype;
	t->params = params;
}


struct param_list *create_param_list(
	char *name,
	struct type *type,
	struct param_list *next
) {
	struct param_list *pl = malloc(sizeof(*pl));
	pl->name = name;
	pl->type = type; 
	pl->next =next;
	return pl;
};