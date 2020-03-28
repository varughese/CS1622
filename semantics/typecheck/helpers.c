#include <stdio.h>
#include <stdlib.h>

int num_errors = 0;

void error_name_resolution(const char* err, const char* sym_name) {
	printf("ERROR: %s - %s\n",err, sym_name);
	num_errors++;
}

void error_type_check(const char* err) {
	printf("ERROR: %s\n",err);
	num_errors++;
}

int get_num_errors() {
	return num_errors;
}