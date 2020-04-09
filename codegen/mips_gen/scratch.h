int scratch_alloc();
void scratch_free(struct expr *e);
const char *scratch_name(struct expr *e);

int *save_registers();
void restore_registers(int *saved_registers);