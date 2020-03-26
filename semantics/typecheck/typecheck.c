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
	// new_list->symbol = params->symbol;
	new_list->next = param_copy(params->next);
	return new_list;
}

struct type* type_copy(struct type *t) {
	if(t == NULL) return NULL;
	struct type* new_type = malloc(sizeof(t));
	new_type->kind = t->kind;
	new_type->params = param_copy(t->params);
	new_type->subtype = type_copy(t->subtype);
	return new_type; 
}

void param_delete(struct param_list *params) {
	if(params == NULL) return;
	param_delete(params->next);
	free(params->name);
	free(params->type->subtype);
	free(params->type);
	free(params->next);
	// free(params->symbol);
}

void type_delete(struct type *t) {
	if(t == NULL) return;
	type_delete(t->subtype);
	param_delete(t->params);
	free(t);
}

struct type *expr_typecheck(struct expr *e) {
	if (e == NULL) return create_type(TYPE_VOID,0,0);

	struct type *lt = expr_typecheck(e->left);
	struct type *rt = expr_typecheck(e->right);

	struct type *result = NULL;

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
			if(lt->kind != TYPE_INTEGER || rt->kind != TYPE_INTEGER) {
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

		case EXPR_ASSIGN:
			if(!type_equals(lt,rt)) {
				error_type_check("Assigning mismatch typed values");
			}
			// I think the type of assignments are irrelevant since it won't have a parent node?
			result = type_copy(lt);
			break;

		// TODO: finish 
		case EXPR_CALL:
		case EXPR_ARG:
		case EXPR_NAME:
		case EXPR_SEMICOLON:
			break;
	}
	type_delete(lt);
	type_delete(rt);
	if(result == NULL) {
		// printf("err\n");
		return create_type(TYPE_VOID, 0 ,0);
	}
	return result;
}


void stmt_typecheck(struct stmt *s) {
	if(s == NULL) return;

	struct type *t = NULL;
	switch(s->kind) {

		case STMT_EXPR:
			t = expr_typecheck(s->expr);
			type_delete(t);
			break;

		case STMT_IF_ELSE:
			// t = expr_typecheck(s->expr);
			// if(t->kind != TYPE_BOOLEAN) {
			// 	error_type_check("Conditional isn't boolean!");
			// }
			// type_delete(t);
			stmt_typecheck(s->body);
			stmt_typecheck(s->else_body);
			break;

		case STMT_ITERATION:
			// t = expr_typecheck(s->expr);
			// if(t->kind != TYPE_BOOLEAN) {
			// 	error_type_check("Conditional ain't boolean!");
			// }
			// type_delete(t);
			stmt_typecheck(s->body);
			break;

		case STMT_COMPOUND:
			stmt_typecheck(s->body);
			break;

		case STMT_RETURN:
			// t = expr_typecheck(s->expr);
			break;
	}

	stmt_typecheck(s->next);
}

void decl_typecheck(struct decl *d) {
	if(d == NULL) return;

	if(d->type->kind == TYPE_FUNCTION) {
		stmt_typecheck(d->code);
	}
	
	decl_typecheck(d->next);
}

int pass_type_checks(struct decl *root) {
	if(root == NULL) return 0;
	printf("hello\n");
	decl_typecheck(root);
	return 1;
}