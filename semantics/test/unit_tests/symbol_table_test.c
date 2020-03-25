#include "../../symbol_table/symbol_table.h"
#include "../../symbol_table/symbol.h"
#include "../../ast/type.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define T_PRINT_GREEN  "\x1B[32m"
#define T_RESET  "\x1B[37m"

struct type *create_int_type() {
	struct type *t = malloc(sizeof(*t));
	t->kind = TYPE_INTEGER;
	t->subtype = NULL;
	t->params = NULL;
}

int main() {
	printf(T_PRINT_GREEN "\nTESTING symbol_table API:\n" T_RESET);

	printf("Testing initialization.\n");
	init_symbol_table();

	printf("Testing enter, exit, scope level\n");
	scope_enter();
	assert(scope_level() == 2);
	scope_enter();
	assert(scope_level() == 3);
	assert(scope_level() == 3);
	scope_exit();
	assert(scope_level() == 2);
	scope_exit();
	assert(scope_level() == 1);

	printf("Testing scope bind\n");
	struct symbol *ming_sym = symbol_create(SYMBOL_GLOBAL, create_int_type(), "ming");
	scope_bind(ming_sym->name, ming_sym);

	printf("Testing scope lookup current (valid key)\n");
	struct symbol *looked_up = scope_lookup_current("ming");
	assert(looked_up->name[0] == 'm' && looked_up->name[1] == 'i');
	assert(looked_up->type->kind == TYPE_INTEGER);
	assert(looked_up == ming_sym);

	printf("Testing scope lookup current (invalid key)\n");
	struct symbol *should_be_null = scope_lookup_current("jawn");
	assert(should_be_null == NULL);

	printf("Testing scope lookup\n");
	assert(scope_level() == 1);

	// mat should not be in there
	assert(scope_lookup("mat") == NULL);
	scope_enter();

	// mat should not be in there
	assert(scope_lookup("mat") == NULL);

	// Can it find ming still
	looked_up = scope_lookup("ming");
	assert(looked_up->name[0] == 'm' && looked_up->name[1] == 'i');
	assert(looked_up == ming_sym);

	// If we add a new symbol can it find that one
	struct symbol *petrucci_sym = symbol_create(SYMBOL_GLOBAL, create_int_type(), "petrucci");
	scope_bind(petrucci_sym->name, petrucci_sym);
	looked_up = scope_lookup("petrucci");
	assert(looked_up->name[0] == 'p');
	assert(looked_up == petrucci_sym);

	// What if we go deeper?
	scope_enter();
	struct symbol *jawn_sym = symbol_create(SYMBOL_GLOBAL, create_int_type(), "jawn");
	scope_bind(jawn_sym->name, jawn_sym);
	assert(scope_lookup("jawn") == jawn_sym);
	assert(scope_lookup("petrucci") == petrucci_sym);
	assert(scope_lookup("ming") == ming_sym);
	assert(scope_lookup("mat") == NULL);
	
	// What if we exit the scope, jawn should no longer be there
	scope_exit();
	assert(scope_lookup("jawn") == NULL);
	assert(scope_lookup("petrucci") == petrucci_sym);
	assert(scope_lookup("ming") == ming_sym);
	
	printf(T_PRINT_GREEN "All tests pass :) !\n\n" T_RESET);
	return 0;
}