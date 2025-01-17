%option noyywrap

%{
	#include "ast/factory.h"
	// This token file is generated by bison 
	#include "parser.tokens.h"
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
"if"							{ return T_IF; }
"else"							{ return T_ELSE; }
"while"							{ return T_WHILE; }
"int"							{ return T_INT; }
"void"							{ return T_VOID; }
"return"						{ return T_RETURN; }

{LETTER}({LETTER}|{DIGIT})*		{ yylval.name = strdup(yytext); return T_ID;  }
{DIGIT}+(\.{DIGIT}+)?			{ yylval.intval = atoi(yytext); return T_NUM; }

	/* This defines comments using start conditions, which is explained in the flex 
	   man pages. */
"/*"         					{ BEGIN(comment); comment_line_number = 0; }
<comment>[^*\n]*        		/* Skip anything that is not a '*' */
<comment>"*"+[^*/\n]*   		/* Skip any '*'s not followed by '/'s */
<comment>\n             		{ comment_line_number++;}
<comment>"*"+"/"        		{ BEGIN(INITIAL); line_number += comment_line_number;}
<comment><<EOF>>				{ /* return ERROR_UNCLOSED_COMMENT; */ }
	/* End of comments definition */

"="                     return T_EQUAL;
"=="                    return T_ISEQ;
"!="                    return T_NEQ;
"<"                     return T_LT;
"<="                    return T_LE;
">"                     return T_GT;
">="                    return T_GE;
"("                     return T_LPAREN;
")"                     return T_RPAREN;
"["                     return T_LBRACKET;
"]"                     return T_RBRACKET;
"{"                     return T_LBRACE;
"}"                     return T_RBRACE;
"."                     return T_DOT;
","                     return T_COMMA;
"+"                     return T_PLUS;
"-"                     return T_MINUS;
"*"                     return T_MUL;
"/"                     return T_DIV;
";"                     return T_SEMICOLON;
.						return ERROR_INVALID_CHARACTER;

%%