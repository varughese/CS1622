struct declaration {
	char *name;
	struct type *type; 
	struct expr *value;
	struct stmt *code;
	struct declaration *next;
};

