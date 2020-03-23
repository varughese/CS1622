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