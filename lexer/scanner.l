%{
	#include "token.h"
	int numLines = 0;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
KEYWORD (if)|(else)|(while)|(int)|(void)|(return)
MATH_SYMBOL (\+)|(\-)|(\*)|(\/)
RELATION_SYMBOL (>=)|(<=)|(<)|(>)|(==)|(!=)|(=)
BRACKET_SYMBOL ("(")|(")")|("[")|("]")|("{")|("}")
COMMENTS  ("/*")|("*/")

%%

(" "|\t)						/* Skip whitespace */
\n								{numLines++;}
{KEYWORD}						{return 1;}
{LETTER}({LETTER}|{DIGIT})*		{return 2;}
{DIGIT}+(\.{DIGIT}+)?			{return 3;}
{MATH_SYMBOL}|{RELATION_SYMBOL}|{BRACKET_SYMBOL}|{COMMENTS}|(;)|(,)		{return 4;}
[.]								{return 5;}
%%

int yywrap() { return 1; }

#include "token.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Must provide 2 arguments\n");
		return 1;
	}
	freopen (argv[2],"w",stdout);
	yyin = fopen(argv[1],"r"); 
	while(1) {
		int t = yylex();
		if(t == 0) break;
		printf("(,,%s)\n", yytext);
	}
	fclose(stdout);
	return 0;
}
