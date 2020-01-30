%{
	#include "token.h"
	int comment_line_number = 0;
	int line_number = 1;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
KEYWORD (if)|(else)|(while)|(int)|(void)|(return)
MATH_SYMBOL (\+)|(\-)|(\*)|(\/)
RELATION_SYMBOL (>=)|(<=)|(<)|(>)|(==)|(!=)|(=)
BRACKET_SYMBOL ("(")|(")")|("[")|("]")|("{")|("}")

%x comment
%%

(" "|\t)						/* Skip whitespace */
\n								{line_number++;}
{KEYWORD}						{return TOKEN_KEY;}
{LETTER}({LETTER}|{DIGIT})*		{return TOKEN_ID;}
{DIGIT}+(\.{DIGIT}+)?			{return TOKEN_NUM;}

"/*"         			{ comment_line_number = 0; BEGIN(comment);} /* Comments, got help from Flex man pages */
<comment>[^*\n]*        /* Not a '*' */
<comment>"*"+[^*/\n]*   /* '*'s not followed by '/'s */
<comment>\n             { comment_line_number++;}
<comment>"*"+"/"        { line_number += comment_line_number; BEGIN(INITIAL);}
<comment><<EOF>>		{ return TOKEN_ERROR_UNCLOSED_COMMENT; }

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
	char * lexeme; 
	while(1) {
		int token = yylex();
		if (token == TOKEN_EOF) {
			break;
		}
		if(token == TOKEN_ERROR_UNCLOSED_COMMENT) {
			lexeme = "/*";
		} else {
			lexeme = yytext;
		}
		printf("(%d,%s,\"%s\")\n", line_number, tokenToString(token), lexeme);
		if(token == TOKEN_ERROR || token == TOKEN_ERROR_UNCLOSED_COMMENT) {
			break;
		}
	}
	fclose(stdout);
	return 0;
}
