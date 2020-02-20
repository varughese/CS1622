all: parser

parser.tab.c paser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

parser: lex.yy.c parser.tab.c parser.tab.h
	gcc -o parser parser.tab.c lex.yy.c

clean:
	rm parser parser.tab.c lex.yy.c calc.tab.h