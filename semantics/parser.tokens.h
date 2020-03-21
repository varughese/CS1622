/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TOKENS_H_INCLUDED
# define YY_YY_PARSER_TOKENS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_IF = 258,
    T_ELSE = 259,
    T_WHILE = 260,
    T_INT = 261,
    T_VOID = 262,
    T_RETURN = 263,
    T_ID = 264,
    T_NUM = 265,
    T_EQUAL = 266,
    T_ISEQ = 267,
    T_NEQ = 268,
    T_LT = 269,
    T_LE = 270,
    T_GT = 271,
    T_GE = 272,
    T_LPAREN = 273,
    T_RPAREN = 274,
    T_LBRACKET = 275,
    T_RBRACKET = 276,
    T_LBRACE = 277,
    T_RBRACE = 278,
    T_COMMA = 279,
    T_PLUS = 280,
    T_MINUS = 281,
    T_MUL = 282,
    T_DIV = 283,
    T_SEMICOLON = 284,
    T_DOT = 285,
    ERROR_UNCLOSED_COMMENT = 286,
    ERROR_INVALID_CHARACTER = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 25 "parser.bison" /* yacc.c:1909  */

    struct decl *decl;
	struct stmt *stmt;
	struct expr *expr;
	struct type *type;
	struct param_list *param_list;
	expr_t expr_t;
	int intval;
	char *name;

#line 98 "parser.tokens.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TOKENS_H_INCLUDED  */
