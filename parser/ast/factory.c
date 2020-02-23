#include <stdio.h>
#include <stdlib.h>
#include "decl.h"
#include "expr.h"
#include "stmt.h"
#include "type.h"

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