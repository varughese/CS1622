%option noyywrap

%{
	#include "parser.tab.h"

	#define YY_DECL int yylex()

	int comment_line_number = 0;
	int line_number = 1;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
KEYWORD (if)|(else)|(while)|(int)|(void)|(return)
MATH_SYMBOL (\+)|(\-)|(\*)|(\/)
RELATION_SYMBOL (>=)|(<=)|(<)|(>)|(==)|(!=)|(=)
BRACKET_SYMBOL ("(")|(")")|("[")|("]")|("{")|("}")
SYMBOL {MATH_SYMBOL}|{RELATION_SYMBOL}|{BRACKET_SYMBOL}|(;)|(,)

%x comment
%%

(" "|\t)						/* Skip whitespace */
\n								{ line_number++; 	}
{KEYWORD}						{ return TOKEN_KEY; }
{LETTER}({LETTER}|{DIGIT})*		{ return TOKEN_ID;  }
{DIGIT}+(\.{DIGIT}+)?			{ yylval.fval = atof(yytext); return TOKEN_NUM; }

	/* This defines comments using start conditions, which is explained in the flex 
	   man pages. */
"/*"         					{ BEGIN(comment); comment_line_number = 0; }
<comment>[^*\n]*        		/* Skip anything that is not a '*' */
<comment>"*"+[^*/\n]*   		/* Skip any '*'s not followed by '/'s */
<comment>\n             		{ comment_line_number++;}
<comment>"*"+"/"        		{ BEGIN(INITIAL); line_number += comment_line_number;}
<comment><<EOF>>				{ return ERROR_UNCLOSED_COMMENT; }
	/* End of comments definition */

{SYMBOL}						{ return TOKEN_SYM;}
.								{ return ERROR_INVALID_CHARACTER; }

%%
