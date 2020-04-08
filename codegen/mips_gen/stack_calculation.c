#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "../symbol_table/symbol.h"
#include "stack_calculation.h"

void set_stack_positions_on_variables(struct decl *fd, struct decl *local_decl);
int set_stack_positions_for_parameters(struct param_list* params, int local_vars_count);

void find_variables_in_stmt(struct decl *d, struct stmt *stmt) {
	if(stmt == NULL) return;

	// We need this helper function to recursively traverse the tree and find
	// all compound statements in this function

	if (stmt->kind == STMT_COMPOUND) {
		if (stmt->decl != NULL) {
			set_stack_positions_on_variables(d, stmt->decl);
		}
		find_variables_in_stmt(d, stmt->body);
	} else if (stmt->kind == STMT_ITERATION) {
		find_variables_in_stmt(d, stmt->body);
	} else if (stmt->kind == STMT_IF_ELSE) {
		find_variables_in_stmt(d, stmt->body);
		find_variables_in_stmt(d, stmt->else_body);
	}

	find_variables_in_stmt(d, stmt->next);	
}

void set_stack_positions_on_variables(struct decl *fd, struct decl *local_decl) {
	// This function exists because we need to set the appropiate indicators
	// on variables in order to make variable address calculation on the stack possible
	// Things to keep in mind:
	// A callee puts arguments onto the stack. Then, the caller puts the $ra, then
	// all local variables.
	
	// So [a1, a0, $ra, c, x[3], x[2], x[1], x, b] represents the stack for a function
	// void f(int a0, int a1) {
	// 		int b; int x[4]; int c;
	// }
	
	// We need to update the `stack_pos` value on all of the symbols so that stack
	// calculation is easy. Note an array counts as as many local variables as space
	// it takes up. so x[4] counts as 4 local ariables.

	// We compute this recursively, because every compound statement in a function
	// can have more local declarations. Like an if statement might contain variables,
	// which we need to put on the stack.

	if (local_decl == NULL) {
		// This algorithm is messy
		// Loop thru the rest of decl recursively to find ALL local variables
		find_variables_in_stmt(fd, fd->code);
		// Now, local_vars_count is populated with the correct number, since the above
		// call is recursive.
		int param_count = set_stack_positions_for_parameters(fd->type->params, fd->symbol->local_vars_count);
		fd->symbol->params_count = param_count;
	} else {
		int local_variables = fd->symbol->local_vars_count;
		while (local_decl != NULL) {
			local_decl->symbol->stack_position = local_variables;
			if(local_decl->type->kind == TYPE_ARRAY) {
				local_variables += local_decl->array_size;
			} else {
				local_variables++;
			}
			printf("# Local variable [%s], stack_pos [%d] \n", local_decl->symbol->name, local_decl->symbol->stack_position);
			local_decl = local_decl->next;
		}
		fd->symbol->local_vars_count = local_variables;
	}
}


// To make argument stack calculation easier, we increase the `stack_pos` on
// the parameters so symbol_codegen() can easily determine its position on the stack
int set_stack_positions_for_parameters(struct param_list* params, int local_vars_count) {
	struct param_list *current = params;
	int param_count = 0;

	// In the code below, I numbered the variables to show what the `stack_pos` would be
	//
	// void f(int a3, int a4) { 
	// 	int v0; 
	//  int v1; 
	//  { 
	//		int v2 
	//	} 
	// }
	// We can calculate the address of a variable based on this number.

	// We can have nested scopes inside of functions (like an if statement),
	//  so that is a reason why this file seems so convuluted.
	//  we keep track of param_count and the total function_variable_count
	//  so we know exactly how to clear the stack.

	while(current != NULL) {
		current->symbol->stack_position = param_count++ + local_vars_count;
		printf("# parameter [%s], position [%d]\n", current->symbol->name, current->symbol->stack_position);
		current = current->next;
	}

	return param_count;
}

void pre_function(struct decl *d) {
	// The set_stack_positions_on_variables() function will count how many
	// local vars there are and do all stack position calculations for us
	set_stack_positions_on_variables(d, NULL);
	
	printf("\t # %s() [%d] params, [%d] local vars\n", d->name, d->symbol->params_count, d->symbol->local_vars_count);
	// push $ra
	printf("sub $sp, $sp, 4 # push ra\n");
	printf("sw  $ra, 0($sp)\n");

	// By convention, the caller pushes arguments onto the stack before
	// they are called. So, when this function is called, those will be
	// on the stack.
	// So stack looks like this, after we place the RA:
	// Stack [param1, param0, RA]

	// Now, we also reserve spots on the stack for all of the local variables
	// push local vars
	printf("sub $sp, $sp, %d # push local vars\n", 4 * d->symbol->local_vars_count);
	printf("move $fp, $sp\n");
	printf("# {\n");
}


void post_function(struct decl *d) {
	printf("# }\n");
	// pop local vars
	printf("add $sp, $sp, %d # pop local vars\n", 4 * d->symbol->local_vars_count);
	// pop ra
	printf("lw  $ra, ($sp)\n");
	printf("add $sp, $sp, 4\n");
	// pop all arguments
	printf("add $sp, $sp, %d # pop arguments \n", 4 * d->symbol->params_count);
	printf("move $fp, $sp\n");
	// return
	printf("j $ra\n");
}