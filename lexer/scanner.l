%{
	#include "token.h"
	int line_number = 1;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
KEYWORD (if)|(else)|(while)|(int)|(void)|(return)
MATH_SYMBOL (\+)|(\-)|(\*)|(\/)
RELATION_SYMBOL (>=)|(<=)|(<)|(>)|(==)|(!=)|(=)
BRACKET_SYMBOL ("(")|(")")|("[")|("]")|("{")|("}")
COMMENTS  \/\*(\/|([^*][^/])*|.*\/)\*\/
UNOPEN_COMMENTS "/*"[.\n]*[^"*/"]*
%x comment
%%

(" "|\t)						/* Skip whitespace */
\n								{line_number++;}
{KEYWORD}						{return TOKEN_KEY;}
{LETTER}({LETTER}|{DIGIT})*		{return TOKEN_ID;}
{DIGIT}+(\.{DIGIT}+)?			{return TOKEN_NUM;}
"/*"         BEGIN(comment); /* Comments, got help from Flex man pages */
<comment>[^*\n]*        /* Not a '*' */
<comment>"*"+[^*/\n]*   /* '*'s not followed by '/'s */
<comment>\n             {line_number++;}
<comment>"*"+"/"        BEGIN(INITIAL);
{UNOPEN_COMMENTS}				{return TOKEN_ERROR;}
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
		printf("(%d,%s,\"%s\")\n", line_number, tokenToString(token), yytext);
		if(token == TOKEN_ERROR)
		{
			
			break;
		}
	}
	fclose(stdout);
	return 0;
}
