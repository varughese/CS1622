#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "../symbol_table/symbol.h"
#include <string.h>
#include "scratch.h"
#include "mips_gen.h"

int __label_count = 0;
int label_create() {
	return __label_count++;
}

const char *label_name(int label) {
	char *name = malloc(128);
	sprintf(name, "L%d", label);
	return name;
}

void ast_to_mips(struct decl *root) {
	printf("TODO - Turn ast into MIPS lol %s\n", label_name(4));
}