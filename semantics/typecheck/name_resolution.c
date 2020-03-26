#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "../symbol_table/symbol_table.h"
#include "name_resolution.h"
#include "helpers.h"

void expr_resolve(struct expr *d);
void stmt_resolve(struct stmt *d);
void param_list_resolve(struct param_list *pl);

void expr_resolve(struct expr *expr) {
	if(expr == NULL) return;

	if(expr->kind == EXPR_NAME) {
		expr->symbol = scope_lookup(expr->name);
		
		if(expr->symbol == NULL) {
			error_name_resolution("Name doesn't exist",expr->name);
		}

	} else {
		expr_resolve(expr->left);
		expr_resolve(expr->right);
	}
}

void stmt_resolve(struct stmt *stmt) {
	if(stmt == NULL) return;

	if (stmt->kind == STMT_COMPOUND) {
		scope_enter();
		decl_resolve(stmt->decl);
		stmt_resolve(stmt->body);
		scope_exit();
	} else if (stmt->kind == STMT_EXPR) {
		expr_resolve(stmt->expr);
	} else if (stmt->kind == STMT_ITERATION) {
		scope_enter();
		expr_resolve(stmt->expr);
		stmt_resolve(stmt->body);
		scope_exit();
	} else if (stmt->kind == STMT_IF_ELSE) {
		expr_resolve(stmt->expr);
		scope_enter();
		stmt_resolve(stmt->body);
		scope_exit();
		scope_enter();
		stmt_resolve(stmt->else_body);
		scope_exit();
	} else if (stmt->kind == STMT_RETURN) {
		expr_resolve(stmt->expr);
	}

	stmt_resolve(stmt->next);
}

void param_list_resolve(struct param_list *p) {
	if (p == NULL) return;

	p->symbol = symbol_create(SYMBOL_PARAM, p->type, p->name);

	if(scope_lookup_current(p->name)) {
		error_name_resolution("Param Already Defined", p->name);	
	}

	scope_bind(p->name, p->symbol);
	param_list_resolve(p->next);
}

void decl_resolve(struct decl *d) {
	if(d == NULL) return;

	symbol_t kind = scope_level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
	d->symbol = symbol_create(kind, d->type, d->name);

	scope_bind(d->name,d->symbol);
	
	if(d->code) {
		// This is declaration is a function, so enter a new scope.
		scope_enter();
		param_list_resolve(d->type->params);
		stmt_resolve(d->code);
		scope_exit();
	}

	decl_resolve(d->next);
}
