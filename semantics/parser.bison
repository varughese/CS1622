%{

#define YYERROR_VERBOSE

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "ast/factory.h"
#include "ast/tostring.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

struct decl *abstract_syntax_tree;

void yyerror(const char* s);

/* Clunky: Manually declare the interface to the scanner generated by flex. */
extern char *yytext;
%}


%union {
    struct decl *decl;
	struct stmt *stmt;
	struct expr *expr;
	struct type *type;
	struct param_list *param_list;
	expr_t expr_t;
	int intval;
	char *name;
};

%token T_IF T_ELSE T_WHILE
%token T_INT
%token T_VOID
%token T_RETURN
%token<name> T_ID
%token<intval> T_NUM
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
%token T_COMMA
%token T_PLUS
%token T_MINUS
%token T_MUL
%token T_DIV
%token T_SEMICOLON

%token T_DOT
%token ERROR_UNCLOSED_COMMENT
%token ERROR_INVALID_CHARACTER

%left T_PLUS T_MUL
%right T_RPAREN T_ELSE

%type <decl> program declaration_list declaration fun_declaration local_declarations var_declaration
%type <stmt> compound_stmt statement_list statement expression_stmt selection_stmt iteration_stmt return_stmt
%type <expr> expression additive_expression simple_expression term factor var call arg_list args
%type <type> type_specifier
%type <param_list> params param param_list
%type <expr_t> addop mulop relop

%start program
%%

program : declaration_list { abstract_syntax_tree = $$; }

declaration_list : declaration declaration_list { $$ = $1; $1->next = $2;  }
				 | declaration { $$ = $1;  }

declaration : var_declaration
			| fun_declaration

var_declaration : type_specifier T_ID T_SEMICOLON { $$ = create_var_declaration($2, $1);  }
				| type_specifier T_ID T_LBRACKET T_NUM T_RBRACKET T_SEMICOLON { $$ = create_array_var_declaration($2, $1, $4); }

type_specifier : T_INT { $$ = create_type(TYPE_INTEGER, 0, 0); }
			   | T_VOID { $$ = create_type(TYPE_VOID, 0, 0); }

fun_declaration : type_specifier T_ID T_LPAREN params T_RPAREN compound_stmt { 
	$$ = create_function_declaration($2, $1, $4, $6);  
}

params : param_list { $$ = $1; }
	   | T_VOID { $$ = NULL; }

param_list : param T_COMMA param_list { $$ = $1; $1->next = $3; }
		   | param { $$ = $1; }

param : type_specifier T_ID { $$ = create_param_list($2, $1, 0); }
	  | type_specifier T_ID T_LBRACKET T_RBRACKET { 
		  struct type* array = create_type(TYPE_ARRAY, $1, 0);
		  $$ = create_param_list($2, array, 0); 
		}

compound_stmt : T_LBRACE local_declarations statement_list T_RBRACE { 
		$$ = stmt_create_compound_stmt($2, $3);
	}

local_declarations : var_declaration local_declarations  { $$ = $1; $1->next = $2; }
				   | %empty { $$ = NULL; }

statement_list : statement statement_list { $$ = $1; $1->next = $2; }
			   | %empty { $$ = NULL; }

statement : expression_stmt 
		  | compound_stmt
		  | selection_stmt 
	      | iteration_stmt
		  | return_stmt

expression_stmt : expression T_SEMICOLON { $$ = stmt_create_expr($1); }
				| T_SEMICOLON { $$ = stmt_create_semicolon(); }

selection_stmt : T_IF T_LPAREN expression T_RPAREN statement { 
					$$ = stmt_create_if_else($3, $5, 0); 
				}
			   | T_IF T_LPAREN expression T_RPAREN statement T_ELSE statement { 
				   $$ = stmt_create_if_else($3, $5, $7); 
				}

iteration_stmt : T_WHILE T_LPAREN expression T_RPAREN statement { 
					$$ = stmt_create_iteration($3, $5); 
				}

return_stmt : T_RETURN T_SEMICOLON { $$ = stmt_create_return(NULL); } 
			| T_RETURN expression T_SEMICOLON { $$ = stmt_create_return($2); }

expression : var T_EQUAL expression { $$ = create_expr(EXPR_ASSIGN, $1, $3); }
		   | simple_expression { $$ = $1; }

var : T_ID { $$ = expr_create_name($1); }
	| T_ID T_LBRACKET expression T_RBRACKET { 
		$$ = create_expr(EXPR_SUBSCRIPT, expr_create_name($1), $3); 
	}

simple_expression : additive_expression relop additive_expression { $$ = create_expr($2, $1, $3); } 
                  | additive_expression { $$ = $1; }

relop : T_LE { $$ = EXPR_LE; }
	  | T_LT { $$ = EXPR_LT; }
	  | T_GT { $$ = EXPR_GT; }
	  | T_GE { $$ = EXPR_GE; }
	  | T_ISEQ { $$ = EXPR_ISEQ; }
	  | T_NEQ { $$ = EXPR_NEQ; }

additive_expression : additive_expression addop term { $$ = create_expr($2, $1, $3); }
					| term { $$ = $1; }

addop : T_PLUS { $$ = EXPR_ADD; }
	  | T_MINUS { $$ = EXPR_SUB; }

term : term mulop factor { $$ = create_expr($2, $1, $3); }
	 | factor { $$ = $1; }

mulop : T_MUL { $$ = EXPR_MUL; }
	  | T_DIV { $$ = EXPR_DIV; }

factor : T_LPAREN expression T_RPAREN { $$ = $2; }
	   | var { $$ = $1; }
	   | call { $$ = $1; } 
	   | T_NUM { $$ = expr_create_integer_literal(atoi(yytext)); }

call : T_ID T_LPAREN args T_RPAREN { 
	struct expr *n = expr_create_name($1);
	$$ = create_expr(EXPR_CALL, n, $3);
}

args : arg_list { $$ = $1; }
	 | %empty { $$ = NULL; }

arg_list : expression T_COMMA arg_list { $$ = create_expr(EXPR_ARG, $1, $3); }
		 | expression { $$ = create_expr(EXPR_ARG, $1, NULL); }

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

	char *ast = stringify_abstract_syntax_tree(abstract_syntax_tree);
	printf("%s\n", ast);
	free(ast);
	fclose(stdout);
	return 0;
}

void yyerror(const char* s) {
	// This would display the syntax error - printf("ERROR! %s\n", s);
	printf("\n");
	exit(1);
}