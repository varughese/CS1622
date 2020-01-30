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
SYMBOL {MATH_SYMBOL}|{RELATION_SYMBOL}|{BRACKET_SYMBOL}|(;)|(,)

%x comment
%%

(" "|\t)						/* Skip whitespace */
\n								{ line_number++; 	}
{KEYWORD}						{ return TOKEN_KEY; }
{LETTER}({LETTER}|{DIGIT})*		{ return TOKEN_ID;  }
{DIGIT}+(\.{DIGIT}+)?			{ return TOKEN_NUM; }

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

#include "token.h"
#include <stdio.h>

void output_lexeme(enum token tok, char *lexeme) {
	printf("(%d,%s,\"%s\")\n", line_number, token_to_string(tok), lexeme);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Must provide 2 arguments\n");
		return 1;
	}
	freopen (argv[2],"w",stdout);
	yyin = fopen(argv[1],"r"); 
	char * lexeme; 
	while(1) {
		enum token token = yylex();
		lexeme = yytext;

		if (token == TOKEN_EOF) break;
		if (token == ERROR_UNCLOSED_COMMENT) lexeme = "/*";

		output_lexeme(token, lexeme);

		if(is_error_token(token)) break;
	}
	fclose(stdout);
	return 0;
}
