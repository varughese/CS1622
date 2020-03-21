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