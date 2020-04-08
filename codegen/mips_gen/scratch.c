#include <stdio.h>
#include <stdlib.h>
#include "../ast/factory.h"
#include "scratch.h"

// Mips has t0, t1 .. t7 which are temporary registers
#define MIPS_TEMP_REGISTERS 8

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
	static const char *register_names[] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7"};
    return (char *) register_names[e->reg];
}