#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "../symbol_table/symbol.h"
#include <string.h>
#include "scratch.h"
#include "mips_gen.h"

void decl_codegen(struct decl *d);

int _label_count = 0;
int label_create() {
	return _label_count++;
}
const char *label_name(int label) {
	char *name = malloc(128);
	sprintf(name, "_L%d", label);
	return name;
}

const char *symbol_codegen(struct symbol *s) {
	// "Stack and Variables Example" section of README.md in example_mips folder 
	// explains the calculations here
	char *name;
	switch(s->kind) {
		case SYMBOL_GLOBAL:
			return s->name;
		case SYMBOL_LOCAL:
			name = malloc(128);
			sprintf(name, "%d($sp)", 4*s->which);
			return name;
		case SYMBOL_PARAM:
			name = malloc(128);
			// We add 4, because $ra is in that spot
			sprintf(name, "%d($sp)", 4*s->which + 4);
			return name;
	}
}

void expr_codegen(struct expr *e) {
	switch(e->kind) {
		case EXPR_INTEGER_LITERAL:
			e->reg = scratch_alloc();
			printf("li %s, %d\n", scratch_name(e->reg), e->integer_value);
			break;

		case EXPR_NAME:
			e->reg = scratch_alloc();
			printf("lw %s, %s\n", scratch_name(e->reg), symbol_codegen(e->symbol));
			break;
		case EXPR_ASSIGN:
			expr_codegen(e->right);
			// `x = 4.` 
			// codegen(e->right) will generate: li $t 4
			// here, we want to do sw $t x
			// where $t is e->right's register, and x is the variable
			// The value we want to store into is now in e->right's register
			printf("sw %s %s\n", scratch_name(e->right->reg), symbol_codegen(e->left->symbol));
			break;

		case EXPR_ADD:
		case EXPR_SUB:
		case EXPR_MUL:
		case EXPR_DIV:
			break;

		case EXPR_ISEQ:
		case EXPR_NEQ:
		case EXPR_LE:
		case EXPR_LT:
		case EXPR_GT:
		case EXPR_GE:
			break;

		case EXPR_SUBSCRIPT:
			break;
		case EXPR_CALL:
			break;
		case EXPR_ARG:
			break;

		default:
			break;
	}
}

void stmt_codegen(struct stmt *s) {
	if(s == NULL) return;
	switch(s->kind) {
		case STMT_COMPOUND:
			decl_codegen(s->decl);
			stmt_codegen(s->body);
			break;

		case STMT_EXPR:
			expr_codegen(s->expr);
			break;

		case STMT_IF_ELSE:
			// stmt_codegen(s->body);
			// stmt_codegen(s->else_body);
			break;

		case STMT_ITERATION:
			// expr_codegen(s->expr);
			// stmt_codegen(s->body);
			break;

		case STMT_RETURN:
			// expr_codegen(s->expr);
			break;
	}

	stmt_codegen(s->next);	
}

// To make argument stack calculation easier, we increase the `which` on
// the parameters so symbol_codegen() can easily determine its position on the stack
void increase_param_symbol_which(struct param_list* params, int local_vars_count) {
	struct param_list *current = params;
	while(current != NULL) {
		current->symbol->which += local_vars_count;
		printf("# parameter [%s], position [%d]\n", current->symbol->name, current->symbol->which);
		current = current->next;
	}
}

void pre_function(struct decl *d) {
	increase_param_symbol_which(d->type->params, d->symbol->local_vars_count);
	printf("\t # %s() [%d] params, [%d] local vars\n", d->name, d->symbol->params_count, d->symbol->local_vars_count);
	// push $ra
	printf("sub $sp, $sp, 4 # push ra\n");
	printf("sw $ra, 0($sp)\n");

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
	printf("lw $ra, ($sp)\n");
	printf("add $sp, $sp, 4\n");
	// pop all arguments
	printf("add $sp, $sp, %d # pop arguments \n", 4 * d->symbol->params_count);
	// return
	printf("j $ra\n");
}

void decl_codegen(struct decl *d) {
	if (d == NULL) return;

	struct symbol *sym = d->symbol;

	if (d->type->kind == TYPE_INTEGER) {
		const char *var_name = symbol_codegen(sym);
		switch (sym->kind) {
			case SYMBOL_GLOBAL:
				printf(".data\n%s: .word 622 # Globals are not initialized in C-, so we put Mings bday. \n\n", var_name);
				printf(".text\n");
				break;
			case SYMBOL_LOCAL:
				printf("# declare local variable [%s], pos [%d] \n", sym->name, sym->which);
				break;
			case SYMBOL_PARAM:
				printf("TODO - I do not think this should ever happen\n.");
				break;
		}
		free((char *) var_name);
	}

	if (d->type->kind == TYPE_FUNCTION) {
		printf("_f_%s:\n", d->symbol->name);
		pre_function(d);
		stmt_codegen(d->code);
		// TODO, we need to clear up the stack, so, we need
		// to figure out how many parameters + variables there were,
		// probably with the last ->which, and then `add $sp, $sp, 4` for each
		post_function(d);
		printf("\n");
	}

	decl_codegen(d->next);
}


void include_output_input_functions() {
	printf("_f_output:\nsub $sp, $sp, 4\nsw $ra, 0($sp)\nlw $a0, 4($sp)\n");
	printf("li $v0, 1\nsyscall\nli $v0, 11\nli $a0, 0x0a\nsyscall\n\n");
}

void ast_to_mips(struct decl *root) {
	printf(".text\n");
	include_output_input_functions();
	decl_codegen(root);
	printf("\n# TODO - Turn ast into MIPS lol\n");
	printf("main:\n");
	printf("jal _f_main\n");
	printf("li $v0, 10 # We need to do this syscall to exit\n");
	printf("syscall # Or else it will error!\n");
}