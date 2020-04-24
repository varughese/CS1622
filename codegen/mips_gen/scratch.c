#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "scratch.h"

// Mips has t0, t1 .. t7 which are temporary registers
#define MIPS_TEMP_REGISTERS 8

const char *temp_name(int reg);

int t_registers[MIPS_TEMP_REGISTERS] = {0, 0, 0, 0, 0, 0, 0, 0};

// This finds a free $t register, a temporary register 
int scratch_alloc() {
	int i;
	for(i=0; i < MIPS_TEMP_REGISTERS; i++) {
		if (t_registers[i] == 0) {
			t_registers[i] = 1;
			return i;
		}
	}

	fprintf(stderr, "Ran out of registers.\n");
	return -1;
}

void scratch_free(struct expr *e) {
	t_registers[e->reg] = 0;
	if (e->symbol && e->symbol->reg >= 0) {
		e->symbol->reg = -1;
	}
}

const char *scratch_name(struct expr *e) {
    return temp_name(e->reg);
}

const char *temp_name(int reg) {
	static const char *register_names[] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7"};
	return (char *) register_names[reg];
}

const char *saved_name(int reg) {
	static const char *register_names[] = {"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7"};
    return (char *) register_names[reg];
}

int *save_registers() {
	int *saved_registers = malloc(MIPS_TEMP_REGISTERS * sizeof(int));
	int i;
	for(i=0; i < MIPS_TEMP_REGISTERS; i++) {
		if (t_registers[i] == 1) {
			// push $s
			printf("sub $sp, $sp, 4\n");
			printf("sw  %s, ($sp)\n", saved_name(i));
			// $s = $t
			printf("move %s, %s\n", saved_name(i), temp_name(i));
		}
		saved_registers[i] = t_registers[i];
		t_registers[i] = 0;
	}
	return saved_registers;
}

int restore_registers(int *saved_registers) {
	int i;
	int restore_count = 0;
	for(i=0; i < MIPS_TEMP_REGISTERS; i++) {
		if (saved_registers[i] == 1) {
			// $t = $s
			printf("move %s, %s\n", temp_name(i), saved_name(i));
			// pop $s
			printf("lw  %s, ($sp)\n", saved_name(i));
			printf("add $sp, $sp, 4\n");
			restore_count++;
			t_registers[i] = 1;
		}
	}
	free(saved_registers);
	return restore_count;
}

void restore_frame_pointer(int restored_register_count) {
	// We need to the following line because the saving of the 
	// registers changes the stack pointer when we push them on
	// the stack, and that in turns changes the frame pointer 
	// when we return from a function
	printf("addi $fp, $fp, %d\n", restored_register_count*4);
	
}
