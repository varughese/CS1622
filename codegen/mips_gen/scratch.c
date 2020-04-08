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
	printf("# %s freed from register %d\n", e->name, e->reg);
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


int *used_registers() {
	int *regs = malloc(MIPS_TEMP_REGISTERS * sizeof(int));
	return regs;
}

int *save_registers(int temp_registers[]) {
	int *regs = malloc(MIPS_TEMP_REGISTERS * sizeof(int));
	return regs;	
}

void restore_registers(int temp_registers[], int saved_registers[]) {
	free(temp_registers);
	free(saved_registers);
}

