#include <stdio.h>
#include <stdlib.h>

#define DISPLAY_TYPECHECK_ERRORS 0

int num_errors = 0;

void error_name_resolution(const char* err, const char* sym_name) {
	#ifdef DISPLAY_TYPECHECK_ERRORS
	#if DISPLAY_TYPECHECK_ERRORS > 0
		printf("ERROR: %s - %s\n",err, sym_name);
	#endif
	#endif
	num_errors++;
}

void error_type_check(const char* err) {
	#ifdef DISPLAY_TYPECHECK_ERRORS
	#if DISPLAY_TYPECHECK_ERRORS > 0
		printf("ERROR: %s\n",err);
	#endif
	#endif
	num_errors++;
}

int get_num_errors() {
	return num_errors;
}