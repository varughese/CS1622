all: parser

parser.tab.c parser.tab.h: parser.bison
	bison -dv parser.bison

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

parser: lex.yy.c parser.tab.c parser.tab.h
	gcc -o parser parser.tab.c lex.yy.c

clean:
	rm parser parser.tab.c lex.yy.c parser.tab.h parser.output