#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "factory.h"

#define MAX_TREE_STRING_LENGTH 10000


/************************************
 	EXPR NODES 
 ***********************************/
char *expr_to_string(struct expr *expr) {
	if (expr == NULL) return "";

	char *operation = malloc(100);
	switch(expr->kind) {
		case EXPR_ADD:
			strcpy(operation, "+");
			break;
		case EXPR_SUB:
			strcpy(operation, "-");
			break;
		case EXPR_MUL:
			strcpy(operation, "*");
			break;
		case EXPR_ASSIGN:
			strcpy(operation, "=");
			break;
		case EXPR_CALL:
			strcpy(operation, "call");
			break;
		case EXPR_SUBSCRIPT:
			strcpy(operation, "");
			break;
		case EXPR_LE:
			strcpy(operation, "<=");
			break;
		case EXPR_LT:
			strcpy(operation, "<");
			break;
		case EXPR_GT:
			strcpy(operation, ">");
			break;
		case EXPR_GE:
			strcpy(operation, ">=");
			break;
		case EXPR_ISEQ:
			strcpy(operation, "==");
			break;
		case EXPR_NEQ:
			strcpy(operation, "!=");
			break;
		case EXPR_DIV:
			strcpy(operation, "/");
			break;
		case EXPR_SEMICOLON:
			strcpy(operation, ";");
			break;
		case EXPR_NAME:
			sprintf(operation, "var [%s]", expr->name);
			break;
		case EXPR_INTEGER_LITERAL:
			sprintf(operation, "%d", expr->integer_value);
			break;
	}
	return operation;
}

char *repeat_tabs(int num_tabs) {
	if (num_tabs == 0) return "";
	int i;
	char *s = malloc(num_tabs+1);
    for (i = 0; i < num_tabs ; i++){ 
        s[i] = '\t'; 
    } 
	s[num_tabs] = '\0';
	return s;
}

char *stringify_args(struct expr *expr);
char *stringify_array(struct expr *expr);

char *stringify_expr_helper(struct expr *expr) {
	if (expr == NULL) { return ""; }
	/* Some expressions are printed differently, so we handle
	 them first */
	if (expr->kind == EXPR_CALL) {
		return stringify_args(expr);
	}
	if (expr->kind == EXPR_SUBSCRIPT) {
		return stringify_array(expr);
	}
	char *output = malloc(5000);
	char *current = expr_to_string(expr);
	char *left = stringify_expr_helper(expr->left);
	char *right = stringify_expr_helper(expr->right);
	char *lspace = (expr->left != NULL) ? " " : ""; 
	char *rspace = (expr->right != NULL) ? " " : ""; 
	sprintf(output, "[%s%s%s%s%s]", current, lspace, left, rspace, right);
	free(current);
	return output;
}

char *stringify_array(struct expr *expr) {
	char *output = malloc(5000);
	if (expr == NULL) { return ""; }
	if (expr->kind != EXPR_SUBSCRIPT) return "Error, stringify_array called on non EXPR_SUBSCRIPT node";
	if (expr->left->kind != EXPR_NAME) return "Error, EXPR_SUBSCRIPT node does not have var on left";
	char *left = stringify_expr_helper(expr->left);
	char *right = stringify_expr_helper(expr->right);
	sprintf(output, "[var [%s]%s]", expr->left->name, right);
	return output;
}

char *stringify_args(struct expr *expr) {
	char *output = malloc(5000);
	if (expr == NULL) { return ""; }
	if (expr->kind != EXPR_CALL) return "Error, stringify_args called on non EXPR_CALL node";
	if (expr->left->kind != EXPR_NAME) return "Error, EXPR_CALL node does not have var on left";

	char *arg_list = malloc(5000);
	sprintf(arg_list, "args");
	char *function_name = malloc(500);
	sprintf(function_name, "%s", expr->left->name);
	struct expr *current_expr_node = expr->right;
	while(current_expr_node != NULL) {
		char *arg_name = stringify_expr_helper(current_expr_node->left);
		sprintf(arg_list, "%s %s", arg_list, arg_name);
		free(arg_name);
		current_expr_node = current_expr_node->right;
	}

	// The format is [call [fn name] [args [] [] [] ] ]
	sprintf(output, "[call [%s] [%s]]", function_name, arg_list);
	free(function_name);
	free(arg_list);
	return output;	
}

void stringify_expr(struct expr *expr) {
	char *res = stringify_expr_helper(expr);
	printf(res);
	free(res);
}

/************************************
 	TYPE NODES 
 ***********************************/


/************************************
 	STATEMENT NODES 
 ***********************************/

/************************************
 	DECLARATION NODES 
 ***********************************/

char *stringify_params(struct param_list *params);

char *stringify_decl(struct decl *decl) {
	if (decl == NULL) return "";
	char *decl_str = malloc(1000);

	if (decl->type->kind == TYPE_FUNCTION) {
		// Function Type
		char *return_type = malloc(40);
		if (decl->type->subtype->kind == TYPE_INTEGER) {
			strcpy(return_type, "int");
		} else if (decl->type->subtype->kind == TYPE_VOID) {
			strcpy(return_type, "void");
		}
		// Function Name
		char *function_name = decl->name;
		// Parameters
		char *param_str = malloc(500);
		sprintf(param_str, stringify_params(decl->type->params));
		sprintf(decl_str, "[fun-declaration [%s] [%s] [%s]]", return_type, function_name, param_str);
		free(return_type);
		free(function_name);
		free(param_str);
	} else if (decl->type->kind == TYPE_INTEGER) {
		sprintf(decl_str, "[var-declaration [int] [%s]]", decl->name);
	} else if (decl->type->kind == TYPE_ARRAY) {
		//todo add /[/] thing
		sprintf(decl_str, "[var-declaration array [%s] [%s] [%s]]", "", "", "");
	}

	return decl_str;
}

char *stringify_params(struct param_list *params) {
	if (params == NULL) { return "params"; }
	char *param_list_str = malloc(5000);
	sprintf(param_list_str, "params");
	
	struct param_list *current_param = params;
	while(current_param != NULL) {
		// Get the typing for the parameter
		char *type = "int"; // Params can only be of type int in this language
		char *name = current_param->name;
		char *array_str;
		if (current_param->type->kind == TYPE_ARRAY) {
			array_str = " [\\[\\]]";
		} else {
			array_str = "";
		}
		char *current_param_str = malloc(300);
		sprintf(current_param_str, "param [%s] [%s]%s", type, name, array_str);

		sprintf(param_list_str, "%s [%s]", param_list_str, current_param_str);
		free(current_param_str);
		current_param = current_param->next;
	}

	// The format is [params [param [type] [name] ]
	return param_list_str;	
}

char *stringify_decl_list(struct decl* root) {
	char *decl_list_string = malloc(5000);
	sprintf(decl_list_string, "");
	struct decl* current = root;
	while (current != NULL) {
		char *decl_str = stringify_decl(current);
		sprintf(decl_list_string, "%s%s", decl_list_string, decl_str);
		free(decl_str); 
		current = current->next;
	}
	return decl_list_string;
}

/************************************
 	ENTRY POINT 
 ***********************************/

char *stringify_abstract_syntax_tree(struct decl* root) {
	char *output = malloc(MAX_TREE_STRING_LENGTH + 20);
	char *program = stringify_decl_list(root);
	sprintf(output, "[program %s]", program);
	return output;
}