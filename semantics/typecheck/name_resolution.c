#include "../ast/factory.h"
#include "../symbol_table/symbol_table.h"

void decl_resolve(struct decl *d) {
	if(!d) return;

	symbol_t kind = scope_level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;

	// d->symbol = symbol_create(kind,d->type,d->name);

	// expr_resolve(d->value);
	scope_bind(d->name,d->symbol);
	
	if(d->code) {
		scope_enter();
		// param_list_resolve(d->type->params);
		// stmt_resolve(d->code);
		scope_exit();
	}

	decl_resolve(d->next);
}