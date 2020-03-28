#include "../ast/factory.h"

int typecheck(struct decl *root);
void param_delete(struct param_list *params);
struct symbol * symbol_copy(struct symbol *s);
struct param_list* param_copy(struct param_list *params);
struct type* type_copy(struct type *t);
struct type *expr_typecheck(struct expr *e);