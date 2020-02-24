%{

#include <stdio.h>
#include <stdlib.h>
#include "ast/decl.h"
#include "ast/expr.h"
#include "ast/stmt.h"
#include "ast/type.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void *parser_result;

void yyerror(const char* s);

%}


%union {
    struct decl *decl;
	// struct stmt *stmt;
	// struct expr *expr;
	// struct type *type;
	// struct param_list *param_list;
	// char *name;
};

%token T_IF T_ELSE T_WHILE
%token T_INT
%token T_VOID
%token T_RETURN
%token T_ID
%token T_NUM
%token T_EQUAL
%token T_ISEQ
%token T_NEQ
%token T_LT
%token T_LE
%token T_GT
%token T_GE
%token T_LPAREN
%token T_RPAREN
%token T_LBRACKET
%token T_RBRACKET
%token T_LBRACE
%token T_RBRACE
%token T_DOT
%token T_COMMA
%token T_PLUS
%token T_MINUS
%token T_MUL
%token T_DIV
%token T_SEMICOLON

%token ERROR_UNCLOSED_COMMENT
%token ERROR_INVALID_CHARACTER

%left T_PLUS T_MUL
%right T_RPAREN T_ELSE

%type <decl> program declaration_list 
// %type <stmt> statement statement_list
// %type <expr> expression additive_expression factor term mulop addop
// %type <type> type_specifier
// %type <param_list> params param param_list
// %type <name> T_ID

%start program
%%

program : declaration_list { parser_result = $$; }

declaration_list : declaration_list declaration { $$ = create_decl(0, 0, 0, 0, 0);  }
				 | declaration { $$ = create_decl(0, 0, 0, 0, 0);  }

declaration : var_declaration
			| fun_declaration

var_declaration : type_specifier T_ID T_SEMICOLON 
				| type_specifier T_ID T_LBRACKET T_NUM T_RBRACKET T_SEMICOLON 

type_specifier : T_INT 
			   | T_VOID

fun_declaration : type_specifier T_ID T_LPAREN params T_RPAREN compound_stmt

params : param_list 
	   | T_VOID

param_list : param_list T_COMMA param 
		   | param

param : type_specifier T_ID 
	  | type_specifier T_ID T_LBRACKET T_RBRACKET 

compound_stmt : T_LBRACE local_declarations statement_list T_RBRACE

local_declarations : local_declarations var_declaration 
				   | %empty

statement_list : statement_list statement 
			   | %empty

statement : expression_stmt 
		  | compound_stmt 
		  | selection_stmt 
	      | iteration_stmt 
		  | return_stmt

expression_stmt : expression T_SEMICOLON 
				| T_SEMICOLON

selection_stmt : T_IF T_LPAREN expression T_RPAREN statement
			   | T_IF T_LPAREN expression T_RPAREN statement T_ELSE statement

iteration_stmt : T_WHILE T_LPAREN expression T_RPAREN statement

return_stmt : T_RETURN T_SEMICOLON | T_RETURN expression T_SEMICOLON

expression : var T_EQUAL expression 
		   | simple_expression

var : T_ID 
	| T_ID T_LBRACKET expression T_RBRACKET

simple_expression : additive_expression relop additive_expression 
                  | additive_expression

relop : T_LE 
	  | T_LT
	  | T_GT
	  | T_GE
	  | T_ISEQ
	  | T_NEQ

additive_expression : additive_expression addop term 
					| term

addop : T_PLUS 
	  | T_MINUS

term : term mulop factor 
	 | factor

mulop : T_MUL 
	  | T_DIV

factor : T_LPAREN expression T_RPAREN 
	   | var 
	   | call 
	   | T_NUM

call : T_ID T_LPAREN args T_RPAREN 

args : arg_list 
	 | %empty

arg_list : arg_list T_COMMA expression 
		 | expression

%%

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Must provide 2 arguments\n");
		return 1;
	}
	freopen (argv[2],"w",stdout);
	yyin = fopen(argv[1],"r"); 

	do {
		yyparse();
	} while(!feof(yyin));

	fclose(stdout);
	return 0;
}

void yyerror(const char* s) {
	exit(1);
}