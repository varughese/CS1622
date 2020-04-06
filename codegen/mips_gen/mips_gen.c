#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "../symbol_table/symbol.h"
#include <string.h>
#include "scratch.h"
#include "mips_gen.h"

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

void decl_codegen(struct decl *d) {
	if (d == NULL) return;

	struct symbol *sym = d->symbol;

	if (d->type->kind == TYPE_INTEGER) {
		if(sym->kind == SYMBOL_GLOBAL) {
			const char *var_name = symbol_codegen(sym);
			printf(".data\n%s: .word 622\n\n", var_name);
		}	
	}

	if (d->type->kind == TYPE_FUNCTION) {
		printf("_f_%s:\n", d->symbol->name);
	}

	decl_codegen(d->next);
}


void include_output_input_functions() {
	printf("_f_output:\nsub $sp, $sp, 4\nsw $ra, 0($sp)\nlw $a0, 4($sp)");
	printf("li $v0, 1\nsyscall\nli $v0, 11\nli $a0, 0x0a\nsyscall\n\n");
}

void ast_to_mips(struct decl *root) {
	include_output_input_functions();
	decl_codegen(root);
	printf("\n# TODO - Turn ast into MIPS lol\n");
	printf("main:\n");
	printf("\tjal _f_main\n");
	printf("\tli $v0, 10 # We need to do this syscall to exit\n");
	printf("\tsyscall # Or else it will error!\n");
}