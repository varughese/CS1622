#include "typecheck.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "helpers.h"
#include "../symbol_table/symbol_table.h"
#include <string.h>

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
	copy->name = s->name;
    return copy;
}

struct param_list* param_copy(struct param_list *params) {
	if(params == NULL) return NULL;
	struct param_list* new_list = malloc(sizeof(*params));
	new_list->name = params->name;
	new_list->type = type_copy(params->type);
	new_list->symbol = symbol_copy(params->symbol);
	new_list->next = param_copy(params->next);
	return new_list;
}

struct type* type_copy(struct type *t) {
	if(t == NULL) return NULL;
	struct type* new_type = malloc(sizeof(*t));
	new_type->kind = t->kind;
	new_type->params = param_copy(t->params);
	new_type->subtype = type_copy(t->subtype);
	return new_type; 
}

void type_delete(struct type *t) {
	if(t == NULL) return;
	param_delete(t->params);
	type_delete(t->subtype);
	free(t);
}

void symbol_delete(struct symbol *s) {
    if (s == NULL) return;
    type_delete(s->type);
    free(s);
}

void param_delete(struct param_list *param) {
	if(param == NULL) return;
	type_delete(param->type);
	symbol_delete(param->symbol);
	param_delete(param->next);
	free(param);
}

void function_typecheck(struct expr *current_arg, struct param_list *current_param) {
	if (current_arg == NULL && current_param == NULL) {
		return;
	}
	if (current_arg == NULL) {
		error_type_check("Function call missing argument");
		return;
	}
	if (current_param == NULL) {
		error_type_check("Function called with too many arguments");
		return;
	}

	struct type *arg_type = expr_typecheck(current_arg);
	struct type *param_type = current_param->type;

	if(!type_equals(arg_type, param_type)) {
		error_type_check("Function called with unexpected argument type");
	}

	type_delete(arg_type);

	function_typecheck(current_arg->right, current_param->next);
}

struct type *expr_typecheck(struct expr *e) {
	if (e == NULL) return create_type(TYPE_VOID,0,0);

	struct type *lt = expr_typecheck(e->left);
	struct type *rt = expr_typecheck(e->right);

	struct type *result = NULL;

	switch(e->kind) {
		case EXPR_INTEGER_LITERAL:
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
				error_type_check("Arithmetic expression type mismatch.");
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
				error_type_check("Can't equate the two types");
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
				error_type_check("Assigning a value of one type to variable of other type.");
			}
			result = type_copy(lt);
			break;

		case EXPR_NAME:
			// TODO need to check if a name is defined
			// int q;
			// int x[3];
			// foo(q);
			// this shouldnt work cuz q is not given a value bu its used
			if (e->symbol == NULL) {
				error_type_check("Variable name not in correct scope! Name resolution likely caught this error");
				// In order to not break the AST, we just say it is void
				result = create_type(TYPE_VOID, 0 ,0);
			} else {
				result = type_copy(e->symbol->type);
			}
			break;

		case EXPR_CALL:
			if (lt->kind != TYPE_FUNCTION) {
				error_type_check("Trying to call a non-function");
				result = create_type(TYPE_VOID, 0 ,0);
			} else {
				function_typecheck(e->right, e->left->symbol->type->params);
				result = type_copy(lt->subtype);
			}
			break;

		case EXPR_ARG:
			// The name or value of an argument is on the left
			result = type_copy(lt);
			break;

		case EXPR_SEMICOLON:
			result = create_type(TYPE_VOID,0,0);
			break;
	}
	type_delete(lt);
	type_delete(rt);
	if(result == NULL) {
		printf("TODO - this should not happne\n");
		return create_type(TYPE_VOID, 0 ,0);
	}
	return result;
}


void stmt_typecheck(struct stmt *s, struct type *subtype) {
	if(s == NULL) return;
	struct type *t = NULL;
	switch(s->kind) {

		case STMT_COMPOUND:
			decl_typecheck(s->decl);
			stmt_typecheck(s->body,subtype);
			break;

		case STMT_EXPR:
			if (s->expr->kind == EXPR_NAME) {
				// This is just a singular expression, like "a;"
				if (s->expr->symbol->type->kind == TYPE_ARRAY) {
					error_type_check("Use of an array name anywhere is invalid except in arguments of function calls.");
				}
			} else {
				t = expr_typecheck(s->expr);
				type_delete(t);
			}
			break;

		case STMT_IF_ELSE:
			t = expr_typecheck(s->expr);
			if(t->kind != TYPE_BOOLEAN) {
				error_type_check("Conditional isn't boolean!");
			}
			type_delete(t);
			stmt_typecheck(s->body,subtype);
			stmt_typecheck(s->else_body,subtype);
			break;

		case STMT_ITERATION:
			t = expr_typecheck(s->expr);
			if(t->kind != TYPE_BOOLEAN) {
				error_type_check("Conditional ain't boolean!");
			}
			type_delete(t);
			stmt_typecheck(s->body,subtype);
			break;

		// TODO: not sure if working
		case STMT_RETURN:
			t = expr_typecheck(s->expr);
			if(!type_equals(t,subtype)) {
				error_type_check("Return value doesn't match return type");
			}
			break;
	}

	stmt_typecheck(s->next,subtype);
}

void typecheck_last_method(struct decl *root) {
	struct decl *last_fn = root;
	while (last_fn->next != NULL) {
		last_fn = last_fn->next;
	}

	if(strcmp(last_fn->name, "main") != 0) {
		error_type_check("Last declaration must be named main");
	}
	if(last_fn->type->kind != TYPE_FUNCTION) {
		error_type_check("Last declaration must be a function");
	} else {
		if(last_fn->type->subtype->kind != TYPE_VOID) {
			error_type_check("Main method must have return type void");
		}
		if(last_fn->type->params != NULL) {
			error_type_check("Main method takes no arguments");
		}
	}
}

void param_list_typecheck(struct param_list *p) {
	struct param_list *current_param = p;
	while(current_param != NULL) {
		if (current_param->type->kind == TYPE_VOID) {
			error_type_check("Parameters cannot have type void");
		}
		current_param = current_param->next;
	}
}

void decl_typecheck(struct decl *d) {
	if(d == NULL) return;

	if(d->type->kind == TYPE_FUNCTION) {
		param_list_typecheck(d->type->params);
		stmt_typecheck(d->code, d->type->subtype);
	} else if(d->type->kind == TYPE_VOID) {
		error_type_check("Cannot have a 'void' variable type");
	}
	
	decl_typecheck(d->next);
}

int pass_type_checks(struct decl *root) {
	if(root == NULL) return 0;
	decl_typecheck(root);
	typecheck_last_method(root);

	return get_num_errors() == 0;
}