all: parser

factory: ast/factory.c ast/factory.h ast/tostring.c ast/tostring.h ast/*.h
	gcc -c ast/factory.c -o ast/factory.o
	gcc -c ast/tostring.c -o ast/tostring.o

symboltable: symbol_table/*
	gcc -c symbol_table/hash_table.c -o symbol_table/hash_table.o
	gcc -c symbol_table/symbol_table.c -o symbol_table/symbol_table.o

typecheck: symboltable typecheck/name_resolution.c typecheck/typecheck.c
	gcc -c typecheck/typecheck.c -o typecheck/typecheck.o
	gcc -c typecheck/name_resolution.c -o typecheck/name_resolution.o

lex.yy.c: scanner.l parser.tokens.h
	flex scanner.l

parser: lex.yy.c semantics.c parser.c parser.tokens.h factory typecheck symboltable
	gcc -o parser parser.c lex.yy.c ast/*.c symbol_table/*.c typecheck/*.c semantics.c 

parser.tab.c parser.tokens.h: parser.bison
	bison -v --defines=parser.tokens.h --output=parser.c parser.bison

clean:
	rm *.o ast/*.o typecheck/*.o main.ast parser parser.tab.c lex.yy.c parser.tokens.h parser.tokens.h parser.output