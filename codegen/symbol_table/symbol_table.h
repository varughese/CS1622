#include "symbol.h"

struct symbol *symbol_create(
	symbol_t kind,
	struct type *type,
	char *name
);

// because this is c, we need to have janky initialize methods
void init_symbol_table();

// causes a new hash table to be pushed on the top of the stack, 
// representing a new scope.
void scope_enter();

// causes topmost hash table to be removed
void scope_exit();

// returns the number of hash tables in current scope
int scope_level();

// add entry to the topmost hash table of stack, mapping name -> sym
void scope_bind(const char *name, struct symbol *sym);

// search the stack of hash tables from top to bottom, looking for the
// etnry that matches name exactly. If none found, return null
struct symbol *scope_lookup(const char *name);

// works like scope_lookup except only looks in the topmost table, so
// checks it in current scope
struct symbol *scope_lookup_current(const char *name);