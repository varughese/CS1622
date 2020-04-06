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
	switch(s->kind) {
		case SYMBOL_GLOBAL:
			return s->name;
		case SYMBOL_LOCAL:
			return "local";
		case SYMBOL_PARAM:
			return "param";
	}
}

void pre_function() {
	printf("# push ra\n");
	printf("sub $sp, $sp, 4\n");
	printf("sw $ra, 0($sp)\n");
}


void post_function() {
	printf("# pop ra\n");
	printf("lw $ra, ($sp)\n");
	printf("add $sp, $sp, 4\n");
	printf("j $ra\n");
}

void expr_codegen(struct expr *expr) {

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

void decl_codegen(struct decl *d) {
	if (d == NULL) return;

	struct symbol *sym = d->symbol;

	if (d->type->kind == TYPE_INTEGER) {
		const char *var_name = symbol_codegen(sym);
		if(sym->kind == SYMBOL_GLOBAL) {
			printf(".data\n%s: .word 622 # Globals are not initialized in C-\n\n", var_name);
		}	
	}

	if (d->type->kind == TYPE_FUNCTION) {
		printf("_f_%s:\n", d->symbol->name);
		pre_function();
		post_function();
	}

	decl_codegen(d->next);
}


void include_output_input_functions() {
	printf("_f_output:\nsub $sp, $sp, 4\nsw $ra, 0($sp)\nlw $a0, 4($sp)");
	printf("li $v0, 1\nsyscall\nli $v0, 11\nli $a0, 0x0a\nsyscall\n\n");
}

void ast_to_mips(struct decl *root) {
	// include_output_input_functions();
	// decl_codegen(root);
	// printf("\n# TODO - Turn ast into MIPS lol\n");
	// printf("main:\n");
	// printf("\tjal _f_main\n");
	// printf("\tli $v0, 10 # We need to do this syscall to exit\n");
	// printf("\tsyscall # Or else it will error!\n");
}