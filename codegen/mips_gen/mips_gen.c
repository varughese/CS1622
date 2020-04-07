#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "../symbol_table/symbol.h"
#include <string.h>
#include "scratch.h"
#include "stack_calculation.h"
#include "mips_gen.h"

void decl_codegen(struct decl *d);

int _label_count = 0;
int label_create() {
	return _label_count++;
}
const char *label_name(int label) {
	char *name = malloc(128);
	sprintf(name, "_L%d", label);
	return name;
}

const char *symbol_codegen(struct symbol *s) {
	// "Stack and Variables Example" section of README.md in example_mips folder 
	// explains the calculations here
	char *name;
	switch(s->kind) {
		case SYMBOL_GLOBAL:
			return s->name;
		case SYMBOL_LOCAL:
			name = malloc(128);
			sprintf(name, "%d($sp)", 4*s->which);
			return name;
		case SYMBOL_PARAM:
			name = malloc(128);
			// We add 4, because $ra is in that spot
			sprintf(name, "%d($sp)", 4*s->which + 4);
			return name;
	}
}

void expr_codegen(struct expr *e) {
	if (e == NULL) return;

	switch(e->kind) {
		case EXPR_INTEGER_LITERAL:
			e->reg = scratch_alloc();
			printf("li  %s, %d\n", scratch_name(e->reg), e->integer_value);
			break;

		case EXPR_NAME:
			e->reg = scratch_alloc();
			printf("lw  %s, %s\n", scratch_name(e->reg), symbol_codegen(e->symbol));
			break;
		case EXPR_ASSIGN:
			expr_codegen(e->right);
			// `x = 4.` 
			// codegen(e->right) will generate: li $t 4
			// here, we want to do sw $t x
			// where $t is e->right's register, and x is the variable
			// The value we want to store into is now in e->right's register
			printf("sw  %s, %s\n", scratch_name(e->right->reg), symbol_codegen(e->left->symbol));
			scratch_free(e->right->reg);
			break;

		case EXPR_ADD:
			expr_codegen(e->left);
			expr_codegen(e->right);
			e->reg = scratch_alloc();
			printf("add %s, %s, %s\n", 
					scratch_name(e->reg), 
					scratch_name(e->left->reg),  
					scratch_name(e->right->reg));
			scratch_free(e->right->reg);
			scratch_free(e->left->reg);
			break;

		case EXPR_SUB:
		case EXPR_MUL:
		case EXPR_DIV:
			break;

		case EXPR_ISEQ:
		case EXPR_NEQ:
		case EXPR_LE:
		case EXPR_LT:
		case EXPR_GT:
		case EXPR_GE:
			break;

		case EXPR_SUBSCRIPT:
			// A subscript is different than declaring an array
			// This is only accessing elements in an array
			break;
		case EXPR_CALL:
			expr_codegen(e->right);
			printf("jal _f_%s\n", e->left->symbol->name);
			e->reg = scratch_alloc();
			printf("move %s $v0\n", scratch_name(e->reg));
			break;
		case EXPR_ARG:
			expr_codegen(e->right);
			expr_codegen(e->left);
			printf("sub $sp, $sp, 4\n");
			printf("sw  %s, ($sp)\n", scratch_name(e->left->reg));
			break;

		default:
			break;
	}
}

void stmt_codegen(struct stmt *s) {
	if(s == NULL) return;
	switch(s->kind) {
		case STMT_COMPOUND:
			// decl_codegen(s->decl); TODO... i dont think we need to do this bc local
			// 	decl's will get taken care of pre_function() method
			stmt_codegen(s->body);
			break;

		case STMT_EXPR:
			expr_codegen(s->expr);
			break;

		case STMT_IF_ELSE:
			// stmt_codegen(s->body);
			// stmt_codegen(s->else_body);
			break;

		case STMT_ITERATION:
			// expr_codegen(s->expr);
			// stmt_codegen(s->body);
			break;

		case STMT_RETURN:
			// expr_codegen(s->expr);
			break;
	}

	stmt_codegen(s->next);	
}

void decl_codegen(struct decl *d) {
	if (d == NULL) return;

	struct symbol *sym = d->symbol;

	if (d->type->kind == TYPE_INTEGER) {
		const char *var_name = symbol_codegen(sym);
		switch (sym->kind) {
			case SYMBOL_GLOBAL:
				printf(".data\n%s: .word 622 # Globals are not initialized in C-, so we put Mings bday. \n\n", var_name);
				printf(".text\n");
				break;
			case SYMBOL_LOCAL:
				printf("# declare local variable [%s], pos [%d] \n", sym->name, sym->which);
				break;
			case SYMBOL_PARAM:
				printf("TODO - I do not think this should ever happen\n.");
				break;
		}
		free((char *) var_name);
	}

	if (d->type->kind == TYPE_FUNCTION) {
		printf("_f_%s:\n", sym->name);
		pre_function(d);
		stmt_codegen(d->code);
		post_function(d);
		printf("\n");
	}

	decl_codegen(d->next);
}


void include_output_input_functions() {
	// void output(int x)
	printf("_f_output:\nsub $sp, $sp, 4\nsw $ra, 0($sp)\nlw $a0, 4($sp)\n");
	printf("li $v0, 1\nsyscall\nli $v0, 11\nli $a0, 0x0a\nsyscall\n");
	printf("lw $ra, ($sp)\nadd $sp, $sp, 4\nadd $sp, $sp, 4\nj $ra\n\n");
	// int input()
	printf("_f_input:\nli  $v0, 5\nsyscall\nj $ra\n\n");
}

void ast_to_mips(struct decl *root) {
	printf(".text\n");
	include_output_input_functions();
	decl_codegen(root);\
	printf("main:\n");
	printf("jal _f_main\n");
	printf("li $v0, 10 # We need to do this syscall to exit\n");
	printf("syscall # Or else it will error!\n");
}