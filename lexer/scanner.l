%{
	#include "token.h"
	int numLines = 1;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
KEYWORD (if)|(else)|(while)|(int)|(void)|(return)
MATH_SYMBOL (\+)|(\-)|(\*)|(\/)
RELATION_SYMBOL (>=)|(<=)|(<)|(>)|(==)|(!=)|(=)
BRACKET_SYMBOL ("(")|(")")|("[")|("]")|("{")|("}")
COMMENTS  \/\*.*\*\/

%%

(" "|\t|{COMMENTS})						/* Skip whitespace */
\n								{numLines++;}
{KEYWORD}						{return TOKEN_ID;}
{LETTER}({LETTER}|{DIGIT})*		{return TOKEN_NUM;}
{DIGIT}+(\.{DIGIT}+)?			{return TOKEN_KEY;}
{MATH_SYMBOL}|{RELATION_SYMBOL}|{BRACKET_SYMBOL}|(;)|(,)		{return TOKEN_SYM;}
[.]								{return TOKEN_ERROR;}
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
		int token = yylex();
		if(token == 0) break;
		printf("(%d,%s,\"%s\")\n", numLines, tokenToString(token), yytext);
	}
	fclose(stdout);
	return 0;
}
