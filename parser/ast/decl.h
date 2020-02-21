struct decl {
	char *name;
	struct type *type; 
	struct expr *value;
	struct stmt *code;
	struct decl *next;
};

struct decl *create_decl(
	char *name,
	struct type *type,
	struct expr *value,
	struct stmt *code,
	struct decl *next
) {
	struct decl *d = malloc(sizeof(*d));
	d->name = name;
	d->type = type;
	d->value = value;
	d->code = code;
	d->next = next;
	return d;
}