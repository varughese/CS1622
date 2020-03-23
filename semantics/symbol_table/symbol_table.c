#include "../ast/factory.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>

struct symbol *symbol_create(
	symbol_t kind,
	struct type *type,
	char *name
) {
	struct symbol *s = malloc(sizeof(*s));
	s->kind = kind;
	s->type = type;
	s->name = name;
	return s;
}

void scope_enter() {}

void scope_exit() {}

int scope_level() {
	return 1;
}

void scope_bind(const char *name, struct symbol *sym) {}

struct symbol *scope_lookup(const char *name) {
	return symbol_create(SYMBOL_LOCAL, NULL, NULL);
}

struct symbol *scope_lookup_current(const char *name) {
	return symbol_create(SYMBOL_LOCAL, NULL, NULL);
}

