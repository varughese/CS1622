#ifndef SYMBOL_H
#define SYMBOL_H

#include "../ast/type.h"

typedef enum {
	SYMBOL_LOCAL,
	SYMBOL_PARAM,
	SYMBOL_GLOBAL
} symbol_t;

struct symbol {
	// kind : local, global, or function parameter
	symbol_t kind; 
	// type : the type, int, function, etc
	struct type *type;
	// name : int x, name is x
	char *name;
	// which : ordinal position of local variables and parameters
	int which;
};

#endif