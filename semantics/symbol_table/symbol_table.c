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
	stack->next = NULL;
	stack->h = hash_table_create(0, 0);;
	stack_size = 1;
}

void hash_table_stack_push(struct hash_table *h) {
	struct stack_node_struct *new_head = (struct stack_node_struct *) malloc(sizeof(struct stack_node_struct));
	
	// Add the new node to the beginning of this linked list
	new_head->h = h;
	new_head->next = stack;
	stack = new_head;

	stack_size++;
}

struct hash_table *hash_table_stack_peek() {
	if(stack_size <= 0 || stack == NULL) {
		printf("Error: Peek called on empty hash table stack.");
	}

	return stack->h;
}

struct hash_table *hash_table_stack_pop() {
	if(stack_size <= 0 || stack == NULL) {
		printf("Error: Pop called on empty hash table stack.");
	}

	// This will hold a reference to the node we want to free
	struct stack_node_struct *zombie; 

	struct hash_table *h = stack->h;

	zombie = stack;
	stack = stack->next;
	free(zombie);
	stack_size--;

	return h;
}

/** Symbol table API **/

int _scope_level = -1;
// This is used to fill `sym->which`. In code generation, this tells us where on the
// stack our variable is defined
int _current_function_variable_count = 0;

void init_symbol_table() {
	init_hash_table_stack();
	_scope_level = 1;
}

void scope_enter() {
	struct hash_table *h = hash_table_create(0, 0);
	hash_table_stack_push(h);
	_scope_level++;
}

void scope_exit() {
	struct hash_table *h = hash_table_stack_pop();
	free(h);
	_scope_level--;
	_current_function_variable_count = 0;
}

int scope_level() {
	if (_scope_level < 1) printf("ERROR: Uninitialized symbol table. Make sure to call init_symbol_table().\n");
	return _scope_level;
}

void scope_bind(const char *name, struct symbol *sym) {
	if (sym->kind != SYMBOL_GLOBAL) {
		sym->which = _current_function_variable_count++;
	}
	struct hash_table *h = hash_table_stack_peek();
	hash_table_insert(h, name, sym);
}

struct symbol *scope_lookup(const char *name) {
	// We cheat a little bit here - we directly use the stack contents
	// in order to traverse the stack like a linked list
	struct stack_node_struct *current = stack;
	while(current != NULL) {
		struct hash_table *h = current->h;
		struct symbol *sym = (struct symbol *) hash_table_lookup(h, name);
		if (sym) return sym;
		
		current = current->next;		
	}
	return NULL;
}

struct symbol *scope_lookup_current(const char *name) {
	struct hash_table *h = hash_table_stack_peek();
	return (struct symbol *) hash_table_lookup(h, name);
}

