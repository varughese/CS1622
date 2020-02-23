all: parser

lex.yy.c: scanner.l parser.tokens.h
	flex scanner.l

parser: lex.yy.c parser.c parser.tokens.h
	gcc -o parser parser.c lex.yy.c

parser.tab.c parser.tokens.h: parser.bison
	bison -v --defines=parser.tokens.h --output=parser.c parser.bison

clean:
	rm main.ast parser parser.tab.c lex.yy.c parser.tokens.h parser.tokens.h parser.output