#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "../symbol_table/symbol.h"
#include <string.h>
#include "scratch.h"
#include "stack_calculation.h"
#include "mips_gen.h"

void decl_codegen(struct decl *d);
void expr_codegen(struct expr *e);


const char *create_label_name(const char *desc) {
	static int _label_count = 0;
	char *name = malloc(128);
	sprintf(name, "__%s%d", desc, _label_count++);
	return name;
} 

const char *return_label_from_fn_name(const char *fn_name) {
	char *name = malloc(128);
	sprintf(name, "_return_%s", fn_name);
	return name;	
}

void define_label(const char *label) { printf("%s:\n", label); }
void branch_to(const char *label) { printf("b %s\n", label); }

const char *symbol_codegen(struct symbol *s) {
	// "Stack and Variables Example" section of README.md in example_mips folder 
	// explains the calculations here
	char *name;
	switch(s->kind) {
		case SYMBOL_GLOBAL:
			return s->name;
		case SYMBOL_LOCAL:
			name = malloc(128);
			sprintf(name, "%d($fp)", 4*s->stack_position);
			return name;
		case SYMBOL_PARAM:
			name = malloc(128);
			// We add 4, because $ra is in that spot
			sprintf(name, "%d($fp)", 4*s->stack_position + 4);
			return name;
	}
}

// This finds the array in memory and loads it into the specified register
void load_array_codegen(struct expr *e, int reg) {
	if (e->symbol->kind == SYMBOL_PARAM) {
		// arrays are passed by reference, so the variable on the stack contains 
		// the address already since it is a parameter
		printf("lw  %s, %s\n",  scratch_name(reg), symbol_codegen(e->symbol));
	} else {
		printf("la  %s, %s\n",  scratch_name(reg), symbol_codegen(e->symbol));
	}
}

// This loads the array AT A SPECIFIC INDEX (like a[1]) into an address and returns the address pointer in MIPS
const char *array_at_index_codegen(struct expr *e) {
	char *array_with_index_pointer = malloc(128);
	int index;

	e->reg = scratch_alloc();
	load_array_codegen(e->left, e->reg);

	if (e->right->kind == EXPR_INTEGER_LITERAL) {
		index = e->right->integer_value;
		sprintf(array_with_index_pointer, "%d(%s)", 4*index, scratch_name(e->reg));
	} else {
		expr_codegen(e->right);
		// Multiply result expression 4 to get index
		printf("sll %s, %s, 2\n", scratch_name(e->right->reg), scratch_name(e->right->reg));
		printf("add %s, %s, %s\n", scratch_name(e->reg), scratch_name(e->reg), scratch_name(e->right->reg));
		scratch_free(e->right->reg);
		sprintf(array_with_index_pointer, "(%s)", scratch_name(e->reg));
	}

	return array_with_index_pointer;
}

void comparision_codegen(struct expr *e) {
	if (e == NULL) return;

	expr_codegen(e->left);
	expr_codegen(e->right);
	e->reg = scratch_alloc();
	const char *reg = scratch_name(e->reg);
	const char *A = scratch_name(e->left->reg);
	const char *B = scratch_name(e->right->reg);  

	switch(e->kind) {
		case EXPR_ISEQ:
			printf("sub %s, %s, %s\n", reg, A, B);
			// Set %s to 1 if it's non-zero
			printf("sltu %s, $zero, %s\n", reg, reg);
			// Flip the lsb so that 0 becomes 1, and 1 becomes 0
			printf("xori %s, %s, 1\n", reg, reg);
			break;
		case EXPR_NEQ:
			printf("sub %s, %s, %s\n", reg, A, B);
			printf("sltu %s, $zero, %s\n", reg, reg);
			break;
		case EXPR_LE:
			printf("sub %s, %s, %s\n", reg, A, B);
			printf("slti %s, %s, 1\n", reg, reg);
			break;
		case EXPR_LT:
			printf("sub %s, %s, %s\n", reg, A, B);
			printf("slt %s, %s, $zero\n", reg, reg);
			break;
		case EXPR_GT:
			printf("sub %s, %s, %s\n", reg, B, A);
			printf("slt %s, %s, $zero\n", reg, reg);
			break;
		case EXPR_GE:
			printf("sub %s, %s, %s\n", reg, B, A);
			printf("slti %s, %s, 1\n", reg, reg);
			break;
		default:
			break;
	}
	scratch_free(e->left->reg);
	scratch_free(e->right->reg);
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
				load_array_codegen(e, e->reg);
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
				variable_address = array_at_index_codegen(e->left);
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
			expr_codegen(e->left);
			expr_codegen(e->right);
			e->reg = scratch_alloc();
			printf("sub %s, %s, %s\n", 
					scratch_name(e->reg), 
					scratch_name(e->left->reg),  
					scratch_name(e->right->reg));
			scratch_free(e->right->reg);
			scratch_free(e->left->reg);
			break;
		case EXPR_MUL:
			expr_codegen(e->left);
			expr_codegen(e->right);
			e->reg = scratch_alloc();
			printf("mul %s, %s, %s\n", 
					scratch_name(e->reg), 
					scratch_name(e->left->reg),  
					scratch_name(e->right->reg));
			scratch_free(e->right->reg);
			scratch_free(e->left->reg);
			break;
		case EXPR_DIV:
			expr_codegen(e->left);
			expr_codegen(e->right);
			e->reg = scratch_alloc();
			printf("div %s, %s, %s\n", 
					scratch_name(e->reg), 
					scratch_name(e->left->reg),  
					scratch_name(e->right->reg));
			scratch_free(e->right->reg);
			scratch_free(e->left->reg);
			break;

		case EXPR_ISEQ:
		case EXPR_NEQ:
		case EXPR_LE:
		case EXPR_LT:
		case EXPR_GT:
		case EXPR_GE:
			comparision_codegen(e);
			break;

		case EXPR_SUBSCRIPT: {
			// A subscript is different than declaring an array
			// This is only accessing elements in an array
			const char *array_with_index_address = array_at_index_codegen(e);
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

void stmt_codegen(struct stmt *s, struct symbol *fn) {
	if(s == NULL) return;
	switch(s->kind) {
		case STMT_COMPOUND:
			stmt_codegen(s->body, fn);
			break;

		case STMT_EXPR:
			expr_codegen(s->expr);
			scratch_free(s->expr->reg);
			break;

		case STMT_IF_ELSE: {
			const char *if_body = create_label_name("if_body");
			const char *else_body = create_label_name("else_body");
			const char *end_if = create_label_name("end_if");
			expr_codegen(s->expr);
			// Everything that is 0 is treated as false, everything thing
			// else is true
			printf("bne %s, $zero %s\n", scratch_name(s->expr->reg), if_body);
			scratch_free(s->expr->reg);
			branch_to(else_body);
			{
				define_label(if_body);
				stmt_codegen(s->body, fn);
			}
			branch_to(end_if);
			{
				define_label(else_body);
				stmt_codegen(s->else_body, fn);
			}
			define_label(end_if);
			break;
		}

		case STMT_ITERATION: {
			const char *while_condition = create_label_name("while_condition");
			const char *while_body = create_label_name("while_body");
			const char *end_while = create_label_name("end_while");
			define_label(while_condition);
			expr_codegen(s->expr);
			printf("bne %s, $zero %s\n", scratch_name(s->expr->reg), while_body);
			branch_to(end_while);
			{
				scratch_free(s->expr->reg);
				define_label(while_body);
				stmt_codegen(s->body, fn);
				branch_to(while_condition);
			}
			define_label(end_while);
			break;
		}

		case STMT_RETURN:
			if (s->expr) {
				expr_codegen(s->expr);
				printf("move $v0, %s\n", scratch_name(s->expr->reg));
			}
			branch_to(return_label_from_fn_name(fn->name));
			break;
	}

	stmt_codegen(s->next, fn);	
}

void decl_codegen(struct decl *d) {
	if (d == NULL) return;

	struct symbol *sym = d->symbol;
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
			stmt_codegen(d->code, sym);
			printf("%s:\n", return_label_from_fn_name(sym->name));
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