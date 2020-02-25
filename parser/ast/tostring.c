#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "factory.h"

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
		case EXPR_DIV:
			strcpy(operation, "/");
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

char *print_args(struct expr *expr, int num_tabs);

char *print_expr_helper(struct expr *expr, int num_tabs) {
	if (expr == NULL) { return ""; }
	if (expr->kind == EXPR_CALL) {
		return print_args(expr, num_tabs);
	}
	char *output = malloc(5000);
	char *current = expr_to_string(expr);
	char *left = print_expr_helper(expr->left, num_tabs + 1);
	char *right = print_expr_helper(expr->right, num_tabs + 1);
	char *lspace = (expr->left != NULL) ? " " : ""; 
	char *rspace = (expr->right != NULL) ? " " : ""; 
	char *tabs = repeat_tabs(num_tabs);
	sprintf(output, "[%s%s%s%s%s]", current, lspace, left, rspace, right);
	free(current);
	return output;
}

char *print_args(struct expr *expr, int num_tabs) {
	char *output = malloc(5000);
	if (expr == NULL) { return ""; }
	if (expr->kind != EXPR_CALL) return "Error, print_args called on non EXPR_CALL node";
	if (expr->left->kind != EXPR_NAME) return "Error, EXPR_CALL node does not have var on left";

	char *arg_list = malloc(5000);
	sprintf(arg_list, "[args");
	char *function_name = malloc(500);
	sprintf(function_name, "[%s]", expr->left->name);
	struct expr *current_expr_node = expr->right;
	while(current_expr_node != NULL) {
		char *arg_name = print_expr_helper(current_expr_node->left, num_tabs);
		sprintf(arg_list, "%s %s", arg_list, arg_name);
		free(arg_name);
		current_expr_node = current_expr_node->right;
	}

	sprintf(output, "[call [%s] %s]", function_name, arg_list);
	free(function_name);
	free(arg_list);
	return output;	
}

void print_expr(struct expr *expr) {
	char *res = print_expr_helper(expr, /*num_tabs =*/ 0);
	printf(res);
	free(res);
}