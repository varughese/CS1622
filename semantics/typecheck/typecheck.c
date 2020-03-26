#include "typecheck.h"
#include <stdio.h>
#include <stdlib.h>

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


int pass_type_checks(struct decl *root) {
	if(root == NULL) return 0;

	return 1;
}