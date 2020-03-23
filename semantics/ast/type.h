/* A type structure encodes the type of every variable and function 
mentioned in a declaration. Primitive types like integer and boolean 
are expressed by simply setting the kind field appropriately, and leaving the
other fields null. Compound types like array and function are built by
connecting multiple type structures together. */

#ifndef TYPE_H
#define TYPE_H

typedef enum {
	TYPE_VOID,
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION
} type_t;

struct type {
	type_t kind;
	struct type *subtype;
	struct param_list *params;
};

struct param_list {
	char *name;
	struct type *type;
	struct param_list *next;
};

#endif