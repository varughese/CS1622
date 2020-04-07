#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "../symbol_table/symbol.h"
#include "stack_calculation.h"

void set_which_ordinals_for_stack_calculation(struct decl *d) {
	// This function exists because we need to set the appropiate indicators
	// on variables in order to make variable address calculation on the stack possible
	// Things to keep in mind:
	// A callee puts arguments onto the stack. Then, the caller puts the $ra, then
	// all local variables.
	
	// So [a1, a0, $ra, c, x[3], x[2], x[1], x, b] represents the stack for a function
	// void f(int a0, int a1) {
	// 		int b; int x[4]; int c;
	// }
	
	// We need to update the `which` value on all of the symbols so that stack
	// calculation is easy. Note an array counts as as many local variables as space
	// it takes up. so x[4] counts as 4 local ariables.
	int local_variables = 0;
	struct decl *local_declaration = d->code->decl;
	printf("# Running thru ordinal counter\n");
	while (local_declaration != NULL) {
		local_declaration->symbol->which = local_variables;
		if(local_declaration->type->kind == TYPE_ARRAY) {
			local_variables += local_declaration->array_size;
		} else {
			local_variables++;
		}
		printf("# Local variable [%s], which [%d] \n", local_declaration->symbol->name, local_declaration->symbol->which);
		local_declaration = local_declaration->next;
	}
	d->symbol->local_vars_count = local_variables;
	// Loop thru the rest of decl recursively to find ALL local variables
	increase_param_symbol_which(d->type->params, d->symbol->local_vars_count);
}


// To make argument stack calculation easier, we increase the `which` on
// the parameters so symbol_codegen() can easily determine its position on the stack
void increase_param_symbol_which(struct param_list* params, int local_vars_count) {
	struct param_list *current = params;
	int param_count = 0;

// 	if (sym->kind != SYMBOL_GLOBAL) {
// 		// All of this code is just to identify the ordinal position
// 		// on the stack the current variable we are binding will point to
// 		// We count the number of parameters, and the total number of variables
// 		// in the function (this includes parameters)
// 		_current_function_variable_count++;

// 		// For parameters, it is just the position in the function header
// 		if (sym->kind == SYMBOL_PARAM) 
// 			sym->which = _current_param_count++;

// 		// For local variables, it is the position in the function, but, we
// 		//	restart at 0. In the code below, I numbered the variables to show
// 		// what the `which` would be
// 		//
// 		// void f(int a0, int a1) { 
// 		// 	int v0; int v1; 
// 		//  { int v2  } }
// 		// In code generation, we update these arguments to make calculation easier.
// 		if (sym->kind == SYMBOL_LOCAL) 
// 			sym->which = _current_function_variable_count - _current_param_count - 1;
// 	} else {
// 		// We can have nested scopes inside of functions (like an if statement),
// 		//  so that is a reason why this code seems more convulted than it needs to be and
// 		//  we keep track of param_count and the total function_variable_count
// 		// Whenever we see a new GLOBAL variable, we have entered
// 		// a new function, so restart the counters
// 		_current_param_count = 0;
// 		_current_function_variable_count = 0;
// 	}

	while(current != NULL) {
		current->symbol->which = param_count++ + local_vars_count;
		printf("# parameter [%s], position [%d]\n", current->symbol->name, current->symbol->which);
		current = current->next;
	}
}

void pre_function(struct decl *d) {
	set_which_ordinals_for_stack_calculation(d);
	
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
	// return
	printf("j $ra\n");
}