/* A declaration states the name, type, and value of 
a symbol so that it can be used in the program. Symbols 
include items such as constants, variables, and functions. */

#ifndef DECL_H
#define DECL_H

#include "../symbol_table/symbol.h"

struct decl {
	char *name;
	struct type *type; 
	int array_size;
	struct stmt *code;
	struct decl *next;
	struct symbol *symbol;
};

#endif