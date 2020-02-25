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

char *print_expr_helper(struct expr *expr) {
	char *output = malloc(5000);
	if(expr == NULL) { return ""; }
	char *current_node = expr_to_string(expr);
	printf("[%s ", current_node);
	print_expr_helper(expr->left);
	print_expr_helper(expr->right);
	printf("]");
	// int output_len = strlen(operation) + strlen(left_string) + strlen(right_string) + 1;
	// snprintf(output, output_len, "[%s %s %s]", operation, left_string, right_string);
	return output;
}

void print_expr(struct expr *expr) {
	// char *res = print_expr_helper(expr);
	// printf("RESULTANT: %s\n", res);
	print_expr_helper(expr);
}