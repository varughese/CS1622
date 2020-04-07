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
	// stack_position : ordinal position of local variables and parameters
	int stack_position;
	// params_count : for a function, we store the number of parameters
	int params_count;
	// local_vars_count : for a function, we store the number of local variables
	int local_vars_count;
};

#endif