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

	return -1;
}

void scratch_free(int r) {
	t_registers[r] = 0;
}

const char *scratch_name(int r) {
	static const char *register_names[] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7"};
    return (char *) register_names[r];
}