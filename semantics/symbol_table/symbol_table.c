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

int _scope_level = 1;

void scope_enter() {
	// TODO
	_scope_level++;
}

void scope_exit() {
	// TODO
	_scope_level--;
}

int scope_level() {
	// TODO
	return _scope_level;
}

void scope_bind(const char *name, struct symbol *sym) {
	// TODO
	printf("SYMBOL_TABLE [%d]: Binding [%s]\n", _scope_level, name);
}

struct symbol *scope_lookup(const char *name) {
	// TODO
	printf("SYMBOL_TABLE [%d]: Looking [%s]\n", _scope_level, name);
	return symbol_create(SYMBOL_LOCAL, NULL, NULL);
}

struct symbol *scope_lookup_current(const char *name) {
	// TODO
	printf("SYMBOL_TABLE [%d]: Looking Current [%s]\n", _scope_level, name);
	return symbol_create(SYMBOL_LOCAL, NULL, NULL);
}

