hash_table: ../../symbol_table/hash_table.c ../../symbol_table/hash_table.h
	gcc ../../symbol_table/hash_table.c -o ../../symbol_table/hash_table.o

test_symbol_table:
	gcc symbol_table_test.c  ../../symbol_table/symbol_table.c ../../symbol_table/hash_table.c -o symbol_table_test
	./symbol_table_test