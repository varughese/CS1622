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
			sprintf(name, "%d($sp)", 4*s->stack_position);
			return name;
		case SYMBOL_PARAM:
			name = malloc(128);
			// We add 4, because $ra is in that spot
			sprintf(name, "%d($sp)", 4*s->stack_position + 4);
			return name;
	}
}

// This loads the array at an index into an address and returns the address pointer in MIPS
const char *array_index_address_codegen(struct expr *e) {
	if (e->left->kind != EXPR_NAME) {
		printf("# TODO - i do not think this should happen\n");
	}
	if (e->right->kind != EXPR_INTEGER_LITERAL) {
		printf("# TODO , expressions in arrays does not work yet\n");
		return "(null)";
	}
	e->reg = scratch_alloc();
	const char *array_pointer = symbol_codegen(e->left->symbol);
	if (e->left->symbol->kind == SYMBOL_PARAM) {
		// parameters are pass by value!
		printf("# Symbol is an array param. Load the pointer.\n");
		printf("lw  %s, %s\n", scratch_name(e->reg), array_pointer);
	} else {
		printf("la  %s, %s\n", scratch_name(e->reg), array_pointer);
	}
	int index = e->right->integer_value;
	char *array_with_index_pointer = malloc(128);
	sprintf(array_with_index_pointer, "%d(%s)", 4*index, scratch_name(e->reg));
	return array_with_index_pointer;
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
			if (e->symbol->type->kind == TYPE_ARRAY) {
				printf("la  %s, %s\n",  scratch_name(e->reg), symbol_codegen(e->symbol));
			} else {
				printf("lw  %s, %s\n", scratch_name(e->reg), symbol_codegen(e->symbol));
			}
			break;
		case EXPR_ASSIGN:
			expr_codegen(e->right);
			// `x = 4.` 
			// codegen(e->right) will generate: li $t 4
			// here, we want to do sw $t x
			// where $t is e->right's register, and x is the variable
			// The value we want to store into is now in e->right's register
			const char *variable_address;
			// Things get a little more complicated if it is an array
			// We handle the case of `arr[3] = 4` here
			if (e->left->kind == EXPR_SUBSCRIPT) {
				variable_address = array_index_address_codegen(e->left);
				scratch_free(e->left->reg);
			} else {
				variable_address = symbol_codegen(e->left->symbol);
			}

			printf("sw  %s, %s\n", scratch_name(e->right->reg), variable_address);
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

		case EXPR_SUBSCRIPT: {
			// A subscript is different than declaring an array
			// This is only accessing elements in an array
			const char *array_with_index_address = array_index_address_codegen(e);
			// Use the variable address register as the same register for
			// both loading the address and then store the value of the
			// array in that register too
			printf("lw  %s, %s\n", scratch_name(e->reg), array_with_index_address);
			break;
		}
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
			scratch_free(e->left->reg);
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
			scratch_free(s->expr->reg);
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
	if (sym->kind != SYMBOL_GLOBAL) {
		printf("TODO - I do not think this should ever happen\n.");
		return;
	}

	const char *var_name = symbol_codegen(sym);
	switch(d->type->kind) {
		case TYPE_INTEGER:
			printf(".data\n%s: .word 0\n\n", var_name);
			printf(".text\n");
			break;

		case TYPE_ARRAY:
			printf(".data\n%s: .word 0:%d \n\n", var_name, d->array_size);
			printf(".text\n");
			break;

		case TYPE_FUNCTION:
			printf("_f_%s:\n", sym->name);
			pre_function(d);
			stmt_codegen(d->code);
			post_function(d);
			printf("\n");
			break;
		
		default:
			break;
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