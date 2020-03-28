#include <stdio.h>
#include <stdlib.h>

void error_name_resolution(const char* err, const char* sym_name) {
	printf("ERROR: %s - %s\n",err, sym_name);
	exit(0);
}

void error_type_check(const char* err) {
	printf("ERROR: %s\n",err);
}