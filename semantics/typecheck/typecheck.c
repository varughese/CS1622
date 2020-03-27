#include "typecheck.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "helpers.h"
#include "../symbol_table/symbol_table.h"

void param_delete(struct param_list *params);
struct symbol * symbol_copy(struct symbol *s);
struct param_list* param_copy(struct param_list *params);
struct type* type_copy(struct type *t);

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

struct symbol * symbol_copy(struct symbol *s) {
    if (s == NULL) return 0;
    struct symbol *copy;
    copy = malloc(sizeof(*copy));
    copy->kind = s->kind;
    copy->which = s->which;
    copy->type = type_copy(s->type);
    return copy;
}

struct param_list* param_copy(struct param_list *params) {
	if(params == NULL) return NULL;
	struct param_list* new_list = malloc(sizeof(params));
	new_list->name = params->name;
	new_list->type = type_copy(params->type);
	new_list->symbol = symbol_copy(params->symbol);
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

void type_delete(struct type *t) {
	if(t == NULL) return;
	type_delete(t->subtype);
	param_delete(t->params);
	free(t);
}

void symbol_delete(struct symbol *s) {
    if (s == NULL) return;
    type_delete(s->type);
    free(s);
}

void param_delete(struct param_list *params) {
	if(params == NULL) return;
	param_delete(params->next);
	free(params->name);
	free(params->type->subtype);
	free(params->type);
	free(params->next);
	symbol_delete(params->symbol);
}

struct type *expr_typecheck(struct expr *e) {
	if (e == NULL) return create_type(TYPE_VOID,0,0);

	struct type *lt = expr_typecheck(e->left);
	struct type *rt = expr_typecheck(e->right);

	struct type *result = NULL;

	switch(e->kind) {
		case EXPR_INTEGER_LITERAL:
			// printf("%p\n",e->name);
			result = create_type(TYPE_INTEGER,0,0);
			break;

		case EXPR_STRING_LITERAL:
			result = create_type(TYPE_STRING,0,0);
			break;

		case EXPR_ADD:
		case EXPR_SUB:
		case EXPR_MUL:
		case EXPR_DIV:
			if(lt->kind != TYPE_INTEGER || rt->kind != TYPE_INTEGER) {
				printf("Arithmetic type mismatch. Using a %p with a %p\n", lt->kind, rt->kind);
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
				printf("Assigning mismatch typed values: %p and %p\n", lt->kind, rt->kind);
			}
			result = type_copy(lt);
			break;

		case EXPR_NAME:
			if(e->symbol->type == TYPE_FUNCTION || e->symbol->type == TYPE_ARRAY) {
				result = type_copy(e->symbol->type->subtype);
			} else {
				result = type_copy(e->symbol->type);
			}
			break;

		case EXPR_CALL:
			result = type_copy(lt);
			break;

		case EXPR_ARG:
			break;

		case EXPR_SEMICOLON:
			result = create_type(TYPE_VOID,0,0);
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


void stmt_typecheck(struct stmt *s, struct type *subtype) {
	if(s == NULL) return;

	struct type *t = NULL;
	switch(s->kind) {

		case STMT_COMPOUND:
			stmt_typecheck(s->body);
			break;

		case STMT_EXPR:
			t = expr_typecheck(s->expr);
			type_delete(t);
			break;

		case STMT_IF_ELSE:
			t = expr_typecheck(s->expr);
			if(t->kind != TYPE_BOOLEAN) {
				error_type_check("Conditional isn't boolean!");
			}
			type_delete(t);
			stmt_typecheck(s->body);
			stmt_typecheck(s->else_body);
			break;

		case STMT_ITERATION:
			t = expr_typecheck(s->expr);
			if(t->kind != TYPE_BOOLEAN) {
				error_type_check("Conditional ain't boolean!");
			}
			type_delete(t);
			stmt_typecheck(s->body);
			break;

		// TODO: not done, have to compare type to the declared type
		case STMT_RETURN:
			t = expr_typecheck(s->expr);
			if(!type_equals(t,subtype)) {
				error_type_check("Return value doesn't match return type");
			}
			break;
	}

	stmt_typecheck(s->next);
}

void decl_typecheck(struct decl *d) {
	if(d == NULL) return;

	if(d->type->kind == TYPE_FUNCTION) {
		stmt_typecheck(d->code, d->type->subtype);
	}
	
	decl_typecheck(d->next);
}

int pass_type_checks(struct decl *root) {
	if(root == NULL) return 0;
	decl_typecheck(root);
	return 1;
}