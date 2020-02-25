all: parser

factory: ast/factory.c ast/factory.h ast/tostring.c ast/tostring.h
	gcc -c ast/factory.c -o ast/factory.o
	gcc -c ast/tostring.c -o ast/tostring.o

lex.yy.c: scanner.l parser.tokens.h
	flex scanner.l

parser: lex.yy.c parser.c parser.tokens.h factory
	gcc -o parser parser.c lex.yy.c ast/*.c

parser.tab.c parser.tokens.h: parser.bison
	bison -v --defines=parser.tokens.h --output=parser.c parser.bison

clean:
	rm *.o ast/*.o main.ast parser parser.tab.c lex.yy.c parser.tokens.h parser.tokens.h parser.output