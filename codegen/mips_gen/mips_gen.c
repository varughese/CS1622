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

	if (d->type->kind == TYPE_FUNCTION) {
		printf("__function :o\n");
	}

	if (d->type->kind == TYPE_INTEGER) {
		if(sym->kind == SYMBOL_GLOBAL) {
			const char *var_name = symbol_codegen(sym);
			printf(".data\n%s: .word 622\n\n", var_name);
		}	
	}

	decl_codegen(d->next);
}


void ast_to_mips(struct decl *root) {
	decl_codegen(root);
	printf("\nTODO - Turn ast into MIPS lol %s\n", label_name(4));
}