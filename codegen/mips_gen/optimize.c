#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "../symbol_table/symbol.h"
#include <string.h>

void decl_optimize(struct decl *d);

// This is simple optimization code that applies constant folding
// and constant propogration. 
// We do not handle cases where there is integer overflow in constant folding
// for simplicity purposes.

struct expr* expr_copy(struct expr *e) {
	if(e == NULL) return NULL;
	struct expr* new_expr = malloc(sizeof(*e));
	new_expr->kind = e->kind;
	new_expr->left = expr_copy(e->left);
	new_expr->right = expr_copy(e->right);
	new_expr->symbol = e->symbol;
	new_expr->integer_value = e->integer_value;
	return new_expr; 
}

void expr_int_literal_delete(struct expr *e) {
	if (e == NULL) return;
	expr_int_literal_delete(e->left);
	expr_int_literal_delete(e->right);
	free(e);
}

struct expr *expr_constant_fold(struct expr *e) {
	if (e == NULL || e->left == NULL || e->right == NULL) return e;
	e->left = expr_constant_fold(e->left);
	e->right = expr_constant_fold(e->right);
	if (e->left->kind == EXPR_INTEGER_LITERAL && 
		e->right->kind == EXPR_INTEGER_LITERAL) {
		int l = e->left->integer_value;
		int r = e->right->integer_value;
		struct expr *f = create_expr(EXPR_INTEGER_LITERAL, 0,0);
		switch(e->kind) {
			case EXPR_ADD:
				f->integer_value = l + r;
				break;
			case EXPR_SUB:
				f->integer_value = l - r;
				break;
			case EXPR_MUL:
				f->integer_value = l * r;
				break;
			case EXPR_DIV:
				f->integer_value = l / r;
				break;
			default:
				return e;
		}
		expr_int_literal_delete(e->left);
		expr_int_literal_delete(e->right);
		return f;
	} else {
		return e;
	}
}


void expr_optimize(struct expr *e) {
	if (e == NULL || e->left == NULL || e->right == NULL) return; 
	switch (e->left->kind) {
		case EXPR_ADD:
		case EXPR_SUB:
		case EXPR_MUL:
		case EXPR_DIV: {
			struct expr *fold = expr_constant_fold(expr_copy(e->left));
			free(e->left);
			e->left = fold;
			break;
		}
		default:
			break;
	}
	switch (e->right->kind) {
		case EXPR_ADD:
		case EXPR_SUB:
		case EXPR_MUL:
		case EXPR_DIV: {
			struct expr *fold = expr_constant_fold(expr_copy(e->right));
			free(e->right);
			e->right = fold;
			break;
		}
		default:
			break;
	}

}


void stmt_optimize(struct stmt *s) {
	if(s == NULL) return;
	switch(s->kind) {

		case STMT_COMPOUND:
			decl_optimize(s->decl);
			stmt_optimize(s->body);
			break;

		case STMT_EXPR:
			expr_optimize(s->expr);
			break;

		case STMT_IF_ELSE:
			expr_optimize(s->expr);
			stmt_optimize(s->body);
			stmt_optimize(s->else_body);
			break;

		case STMT_ITERATION:
			expr_optimize(s->expr);
			stmt_optimize(s->body);
			break;

		case STMT_RETURN:
			break;
	}

	stmt_optimize(s->next);
}

void decl_optimize(struct decl *d) {
	if(d == NULL) return;

	if(d->type->kind == TYPE_FUNCTION) {
		stmt_optimize(d->code);
	}
	
	decl_optimize(d->next);
}

struct decl *optimize_ast(struct decl *root) {
	decl_optimize(root);
	return root;
}