/* The body of a function consists of a sequence of statements. A statement
indicates that the program is to take a particular action in 
the order specified, such as computing a value, performing a loop, 
or choosing between branches of an alternative. A statement can 
also be a declaration of a local variable. Here is the stmt structure:
*/

#ifndef STMT_H
#define STMT_H

typedef enum {
	STMT_COMPOUND,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_ITERATION,
	STMT_RETURN
} stmt_t;

struct stmt {
	stmt_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};

#endif