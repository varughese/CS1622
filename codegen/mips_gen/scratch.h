int scratch_alloc();
void scratch_free(struct expr *e);
const char *scratch_name(struct expr *e);

int *used_registers();
int *save_registers(int temp_registers[]);
void restore_registers(int temp_registers[], int saved_registers[]);