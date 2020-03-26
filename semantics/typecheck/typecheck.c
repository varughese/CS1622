#include "typecheck.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "helpers.h"
#include "../symbol_table/symbol_table.h"

int type_equals(struct type *a, struct type *b) {
	if(a->kind == b->kind) {
		if(a->kind == TYPE_ARRAY) {
			return type_equals(a->subtype, b->subtype);
		} else if (a->kind == TYPE_FUNCTION) {
			return type_equals(a->params->type, b->params->type) &&
				type_equals(a->subtype, b->subtype);
		} else {
			return 1;
		}
	} else {
		return 0;
	}
}

struct param_list* param_copy(struct param_list *params) {
	if(params == NULL) return NULL;
	struct param_list* new_list = malloc(sizeof(params));
	new_list->name = params->name;
	new_list->type = malloc(sizeof(params->type));
	new_list->type->kind = params->type->kind;
	new_list->type->subtype = params->type->subtype;
	new_list->type->params = NULL;
	new_list->symbol = params->symbol;
	new_list->next = param_copy(params->next);
	return new_list;
}

struct type* type_copy(struct type *t) {
	if(t == NULL) return NULL;
	struct type* new_type = malloc(sizeof(t));
	new_type->kind = t->kind;
	new_type->subtype = type_copy(t->subtype);
	new_type->params = param_copy(t->params);
	return new_type; 
}

void param_delete(struct param_list *params) {
	if(params == NULL) return;
	param_delete(params->next);
	free(params->name);
	free(params->type->subtype);
	free(params->type);
	free(params->next);
	free(params->symbol);
}

void type_delete(struct type *t) {
	if(t == NULL) return;
	type_delete(t->subtype);
	param_delete(t->params);
	free(t);
}

struct type *expr_typecheck(struct expr *e) {
	if (!e) return 0;
	struct type *lt = expr_typecheck(e->left);
	struct type *rt = expr_typecheck(e->right);

	struct type *result;

	switch(e->kind) {
		case EXPR_INTEGER_LITERAL:
			result = create_type(TYPE_INTEGER, 0, 0);
			break;

		case EXPR_STRING_LITERAL:
			result = create_type(TYPE_STRING,0,0);
			break;

		case EXPR_ADD:
		case EXPR_SUB:
		case EXPR_MUL:
		case EXPR_DIV:
			if(!type_equals(lt,rt)) {
				error_type_check("Arithmetic type mismatch!");
			}
			result = create_type(TYPE_INTEGER,0,0);
			break;

		case EXPR_ISEQ:
		case EXPR_NEQ:
		case EXPR_LE:
		case EXPR_LT:
		case EXPR_GT:
		case EXPR_GE:
			if(!type_equals(lt,rt)) {
				error_type_check("Equality type mismatch");
			} 

			if(lt->kind == TYPE_VOID ||
			   lt->kind == TYPE_ARRAY ||
			   lt->kind == TYPE_FUNCTION) {
				error_type_check("Can't  equate the two types");
			}
			result = create_type(TYPE_BOOLEAN,0,0);
			break;

		case EXPR_SUBSCRIPT:
			if(lt->kind == TYPE_ARRAY) {
				if(rt->kind != TYPE_INTEGER) {
					error_type_check("Attempting to subscript an array with a non-integer");
				}
				result = type_copy(lt->subtype);
			} else {
				error_type_check("Attempting to subscript a non-array");
				result = type_copy(lt);
			}
			break;
	}
	type_delete(lt);
	type_delete(rt);
}


void stmt_typecheck(struct stmt *s) {
	struct type *t;
	switch(s->kind) {
		case STMT_EXPR:
			t = expr_typecheck(s->expr);
			type_delete(t);
			break;
		case STMT_COMPOUND:
		case STMT_IF_ELSE:
		case STMT_ITERATION:
		case STMT_RETURN:
			break;
	}

	stmt_typecheck(s->next);
}

void decl_typecheck(struct decl *d) {
	if(!d) return;

	if(d->code) {
		stmt_typecheck(d->code);
	}
	decl_typecheck(d->next);
}

int pass_type_checks(struct decl *root) {
	if(root == NULL) return 0;
	decl_typecheck(root);
	return 1;
}