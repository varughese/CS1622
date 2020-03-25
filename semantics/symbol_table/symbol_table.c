#include "../ast/factory.h"
#include "symbol_table.h"
#include "hash_table.h"
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

/** Stack of hash tables implementation **/
int stack_size = 0;
struct stack_node_struct  {
        struct hash_table *h;
        struct stack_node_struct *next;
};

struct stack_node_struct *stack;

void init_hash_table_stack() {
	// We have to do this because we can only malloc inside of functions
	stack = (struct stack_node_struct *) malloc(sizeof(struct stack_node_struct));
}

void hash_table_stack_push(struct hash_table *h) {
	struct stack_node_struct *new_head = (struct stack_node_struct *) malloc(sizeof(struct stack_node_struct));
	
	// Add the new node to the beginning of this linked list
	new_head->h = h;
	new_head->next = stack;
	stack = new_head;

	stack_size++;
}

struct hash_table *hash_table_stack_pop(sh) {
	// This will hold a reference to the node we want to free
	struct stack_node_struct *zombie; 
	
	if(stack_size <= 0 || stack == NULL) {
		printf("Error: Pop called on empty hash table stack.");
	}

	struct hash_table *h = stack->h;

	zombie = stack;
	stack = stack->next;
	free(zombie);
	stack_size--;

	return h;
}

/** Symbol table API **/

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
	return NULL;
}

