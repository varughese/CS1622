all: codegen

factory: ast/factory.c ast/factory.h ast/tostring.c ast/tostring.h ast/*.h
	gcc -c ast/factory.c -o ast/factory.o
	gcc -c ast/tostring.c -o ast/tostring.o

symboltable: symbol_table/*
	gcc -c symbol_table/hash_table.c -o symbol_table/hash_table.o
	gcc -c symbol_table/symbol_table.c -o symbol_table/symbol_table.o

typecheck: symboltable typecheck/name_resolution.c typecheck/typecheck.c
	gcc -c typecheck/typecheck.c -o typecheck/typecheck.o
	gcc -c typecheck/name_resolution.c -o typecheck/name_resolution.o

mips_gen: mips_gen/mips_gen.c mips_gen/scratch.c
	gcc -c mips_gen/mips_gen.c -o mips_gen/mips_gen.o
	gcc -c mips_gen/scratch.c -o mips_gen/scratch.o

lex.yy.c: scanner.l parser.tokens.h
	flex scanner.l

codegen: lex.yy.c codegen.c parser.c parser.tokens.h factory typecheck symboltable mips_gen
	gcc -o codegen parser.c lex.yy.c ast/*.c symbol_table/*.c typecheck/*.c mips_gen/*.c codegen.c 

parser.tab.c parser.tokens.h: parser.bison
	bison -v --defines=parser.tokens.h --output=parser.c parser.bison

.PHONY: test
test:
	cd test/unit_tests/ && make test_symbol_table

.PHONY: run_test_cases
run_test_cases:
	python3 test.py

.PHONY: run
run:
	make && echo '---' && ./codegen main.c main.asm && cat main.asm

.PHONY: clean
clean:
	rm *.o ast/*.o typecheck/*.o main.ast codegen parser.tab.c lex.yy.c parser.tokens.h parser.tokens.h parser.output
