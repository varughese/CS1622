int scratch_alloc();
void scratch_free(struct expr *e);
const char *scratch_name(struct expr *e);

int *save_registers();
int restore_registers(int *saved_registers);
void restore_frame_pointer(int restored_register_count);

void scratch_save_to_stack_if_needed(struct expr *e);
void scratch_load_from_stack_if_needed(struct expr *left, struct expr *right);
