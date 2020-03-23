struct decl {
	char *name;
	struct type *type; 
	int array_size;
	struct stmt *code;
	struct decl *next;
};