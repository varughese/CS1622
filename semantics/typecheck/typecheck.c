#include "typecheck.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "helpers.h"

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
			if(!type_equals(lt,rt)) {
				error_type_check("Addition type mismatch!");
			}
			result = create_type(TYPE_INTEGER,0,0);
			break;
		case EXPR_EQ:
		case EXPR_NEW:
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
	}
	type_delete(lt);
	type_delete(rt);
}



int pass_type_checks(struct decl *root) {
	if(root == NULL) return 0;

	return 1;
}