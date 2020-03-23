<section id="h.p_fJKnrObXyai8" class="yaqOZd" style="">

<div class="mYVXT">

<div class="LS81yb VICjCf" tabindex="-1">

<div class="hJDwNd-AhqUyc-uQSCkd purZT-AhqUyc-II5mzb pSzOP-AhqUyc-qWD73c JNdkSc">

<div class="JNdkSc-SmKAyb">

<div class="" jscontroller="sGwD4d" jsaction="zXBUYb:zTPCnb;oc1XGd:Qxe3nd;" jsname="F57UId">

<div class="oKdM2c Kzv0Me">

<div id="h.p_p_O0Zb4eyai3" class="hJDwNd-AhqUyc-uQSCkd jXK9ad D2fZ2 OjCsFc wHaque GNzUNc">

<div class="jXK9ad-SmKAyb">

<div class="tyJCtd mGzaTb baZpAe">

The C- language specification is excerpted and adapted from the book _**Compiler Construction Principles And Practice** _by Kenneth Louden. The language includes integer variables, functions, and arrays. It has local and global declarations and supports conditions (if-statement) and repetitions (while-statement), as well as supports recursive function calls. It is essentially a subset of C, but is missing some more advanced features, hence its name.

Below you can find the lexical conventions, syntax and semantics description of the language.

## 

<div jscontroller="Ae65rd" jsaction="touchstart:UrsOsc; click:KjsqPd; focusout:QZoaZ; mouseover:y0pDld; mouseout:dq0hvd;fv1Rjc:jbFSOd;CrfLRd:SzACGe;" class="CjVfdc">

<div class="PPhIP rviiZ" jsname="haAclf">

</div>

Lexical Conventions</div>

Here we list the lexical conventions of the language, including a description of the tokens of the language:

1\. The keywords of the language are the following:

```
      else  if  int  return  void  while
```

</div>

_All keywords are reserved, and must be written in lowercase._

2\. Special symbols are the following:

```

      +  -  *  /  <  <=  >  >=  ==  !=  =  ;  ,  (  )  [  ]  {  }  /*  */
```

3\. Other tokens are _**ID**_ and _**NUM**_, defined by the following regular expressions:

```
      ID = letter (letter | digit)*

      NUM = digit digit*

      letter = a | .. | z | A | .. | Z

      digit = 0 | .. | 9
```

_Lower- and uppercase letters are distinct._

4\. White space consists of blanks (' '), newlines ('\n'), and tabs ('\t). White space is ignored except that it must separate _**ID**_’s, _**NUM**_’s, and keywords.

5\. Comments are surrounded by the usual notations **/* … */.** Comments can be placed anywhere white spaces can appear (that is, comments cannot be placed within tokens) and may include more than one line. As in the C language, comments _cannot_ be nested.

## 

<div jscontroller="Ae65rd" jsaction="touchstart:UrsOsc; click:KjsqPd; focusout:QZoaZ; mouseover:y0pDld; mouseout:dq0hvd;fv1Rjc:jbFSOd;CrfLRd:SzACGe;" class="CjVfdc">

<div class="PPhIP rviiZ" jsname="haAclf">

<div role="presentation" class="U26fgb mUbCce fKz7Od LRAOtb rm120e" jscontroller="mxS5xe" jsaction="click:cOuCgd; mousedown:UX7yZ; mouseup:lbsD7e; mouseenter:tfO1Yc; mouseleave:JywGue; focus:AHmuwe; blur:O22p3e; contextmenu:mg9Pef;" jsshadow="" aria-describedby="h.p_f6jdrr4Pyayd" aria-label="Copy heading link" aria-disabled="false" data-tooltip="Copy heading link" aria-hidden="true" data-tooltip-position="top" data-tooltip-vertical-offset="12" data-tooltip-horizontal-offset="0">[<span jsslot="" class="xjKiLb"><span class="Ce1Y1c" style="top: -11px"></span></span>](#h.p_f6jdrr4Pyayd)</div>

</div>

Syntax</div>

A [BNF](https://www.google.com/url?q=https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FExtended_Backus%25E2%2580%2593Naur_form&sa=D&sntz=1&usg=AFQjCNFJXCwywBsfFNjE5Y4bQFdthCeVyg) grammar for C- is as follows:

```
    <program> ::= <declaration-list>

    <declaration-list> ::= <declaration-list> <declaration> | <declaration>

    <declaration> ::= <var-declaration> | <fun-declaration>

    <var-declaration> ::= <type-specifier> ID ; | <type-specifier> ID [ NUM ] ;

    <type-specifier> ::= int | void

    <fun-declaration> ::= <type-specifier> ID ( <params> ) <compound-stmt>

    <params> ::= <param-list> | void

    <param-list> ::= <param-list> , <param> | <param>

    <param> ::= <type-specifier> ID | <type-specifier> ID [ ] 

    <compound-stmt> ::= { <local-declarations> <statement-list> }

    <local-declarations> ::= <local-declarations> <var-declaration> | empty

    <statement-list> ::= <statement-list> <statement> | empty

    <statement> ::= <expression-stmt> | <compound-stmt> | <selection-stmt> 

                  | <iteration-stmt> | <return-stmt>

    <expression-stmt> ::= <expression> ; | ;

    <selection-stmt> ::= if ( <expression> ) <statement> 

                      | if ( <expression> ) <statement> else <statement>

    <iteration-stmt> ::= while ( <expression> ) <statement>

    <return-stmt> ::= return ; | return <expression> ;

    <expression> ::= <var> = <expression> | <simple-expression>

    <var> ::= ID | ID [ <expression> ]

    <simple-expression> ::= <additive-expression> <relop> <additive-expression> 

                           | <additive-expression>

    <relop> ::= <= | < | > | >= | == | !=

    <additive-expression> ::= <additive-expression> <addop> <term> | <term>

    <addop ::= + | -

    <term> ::= <term> <mulop> <factor> | <factor>

    <mulop> ::= * | /

    <factor> ::= ( <expression> ) | <var> | <call> | NUM

    <call> ::= ID ( <args> )

    <args> ::= <arg-list> | empty

    <arg-list> ::= <arg-list> , <expression> | <expression>

```

## 

<div jscontroller="Ae65rd" jsaction="touchstart:UrsOsc; click:KjsqPd; focusout:QZoaZ; mouseover:y0pDld; mouseout:dq0hvd;fv1Rjc:jbFSOd;CrfLRd:SzACGe;" class="CjVfdc">

<div class="PPhIP rviiZ" jsname="haAclf">

</div>

Semantics</div>

For each of those grammar rules we give a short explanation of the associated semantics.

```
    <program> ::= <declaration-list>

    <declaration-list> ::= <declaration-list> <declaration> | <declaration>

    <declaration> ::= <var-declaration> | <fun-declaration>
```
</div>

A program consists of a list (or sequence) of declarations, which may be function or variable declarations, in any order. There must be at least one declaration. Semantic restrictions are as follows (these do not occur in C). All variables and functions must be declared before they are used (this avoids backpatching references): The last declaration in a program must be a function declaration of the form `void main (void)`_**.**_ Note that C- lacks prototypes, so that no distinction is made between declarations and definitions (as in C).

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```
    <var-declaration> ::= <type-specifier> ID ; | <type-specifier> ID [ NUM ] ;

    <type-specifier> ::= int | void
```

</div>

A variable declaration declares either a simple variable of integer type or an array variable whose base type is integer, and whose indices range from `0` . . `_**NUM**_-1`. Note that in C- the only basic types are integer and void. In a variable declaration, only the type specifier _**int**_ can be used. _**Void**_ is for function declarations (see below). Note, also, that only one variable can be declared per declaration.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```
    <fun-declaration> ::= <type-specifier> ID ( <params> ) <compound-stmt>

    <params> ::= <param-list> | void

    <param-list> ::= <param-list> , <param> | <param>

    <param> ::= <type-specifier> ID | <type-specifier> ID [ ] 
```
</div>

A function declaration consists of a return type specifier, an identifier, and a comma-separated list of parameters inside parentheses, followed by a compound statement with the code for the function. If the return type of the function is _**void**_, then the function returns no value (i.e., is a procedure). Parameters of a function are either _**void**_ (i.e., there are no parameters) or a list representing the function's parameters. Parameters followed by brackets are array parameters whose size can vary. Simple integer parameters are passed by value. Array parameters are passed by reference (i.e., as pointers) and must be matched by an array variable during a call. Note that there are no parameters of type "function." The parameters of a function have scope equal to the compound statement of the function declaration, and each invocation of a function has a separate set of parameters. Functions may be recursive (to the extent that declaration before use allows).

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```
    <compound-stmt> ::= { <local-declarations> <statement-list> }
```
</div>

A compound statement is executed by executing the statement sequence in the order given. The local declarations have scope equal to the statement list of the compound statement and supersede any global declarations.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```
    <local-declarations> ::= <local-declarations> <var-declaration> | empty

    <statement-list> ::= <statement-list> <statement> | empty
```
</div>

Note that both declarations and statement lists may be empty. (The non-terminal _empty_ stands for the empty string (epsilon), sometimes written as ε).

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```
    <statement> ::= <expression-stmt> | <compound-stmt> | <selection-stmt> 

                  | <iteration-stmt> | <return-stmt>

    <expression-stmt> ::= <expression> ; | ;
```
</div>

An expression statement has an optional expression followed by a semicolon. Such expressions are usually evaluated for their side effects. Thus, this statement is used for assignments and function calls.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```

    <selection-stmt> ::= if ( <expression> ) <statement> 

                      | if ( <expression> ) <statement> else <statement>

```

The if-statement has the usual semantics: the expression is evaluated; a nonzero value causes execution of the first statement; a zero value causes execution of the second statement, if it exists. This rule results in the classical dangling else ambiguity, which is resolved in the standard way: the else part is always parsed immediately as a substructure of the current if-statement (the "most closely nested" disambiguating rule).

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```
    <iteration-stmt> ::= while ( <expression> ) <statement>
```
</div>

The while-statement is the only iteration statement in C-. It is executed by repeatedly evaluating the expression and then executing the statement if the expression evaluates to a nonzero value, ending when the expression evaluates to 0.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```
    <return-stmt> ::= return ; | return <expression> ;
```
</div>

A return statement may either return a value or not. Functions not declared **void** must return values. Functions declared **void** must not return values. A return causes transfer of control back to the caller (or termination of the program if it is inside **main**).

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```
    <expression> ::= <var> = <expression> | <simple-expression>

    <var> ::= ID | ID [ <expression> ]
```

</div>

An expression is a variable reference followed by an assignment symbol (equal sign) and an expression, or just a simple expression. The assignment has the usual storage semantics: the location of the variable represented by var is found, then the sub-expression to the right of the assignment is evaluated, and the value of the sub-expression is stored at the given location. This value is also returned as the value of the entire expression. A var is either a simple (integer) variable or a sub-scripted array variable. A negative subscript causes the program to halt (unlike C). However, _upper bounds of subscripts are not checked._

Variables represent a further restriction of C- from C. In C the target of an assignment must be an l-value, and l-values are addresses that can be obtained by many operations. In C- the only I-values are those given by the _var_ syntax, and so this category is checked syntactically, instead of during type checking as in C. Thus, pointer arithmetic is forbidden in C-.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```bnf
    <simple-expression> ::= <additive-expression> <relop> <additive-expression> 

                          | <additive-expression>

    <relop> ::= <= | < | > | >= | == | !=
```
</div>

A simple expression consists of relational operators that do not associate (that is an unparenthesized expression can only have one relational operator). The value of a simple expression is either the value of its additive expression if it contains no relational operators, or 1 if the relational operator evaluates to true, or 0 if it evaluates to false.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```bnf
    <additive-expression> ::= <additive-expression> <addop> <term> | <term>

    <addop ::= + | -

    <term> ::= <term> <mulop> <factor> | <factor>

    <mulop> ::= * | /
```
</div>

Additive expressions and terms represent the typical associativity and precedence of the arithmetic operators, The **/** symbol represents integer division; that is, any remainder is truncated.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```bnf
    <factor> ::= ( <expression> ) | <var> | <call> | NUM
```
</div>

A factor is an expression enclosed in parentheses, a variable, which evaluates to the value of its variable; a call of a function, which evaluates to the returned value of the function; or a _**NUM**_, whose value is computed by the scanner. An array variable must be subscripted, except in the case of an expression consisting of a single ID and used in a function call with an array parameter (see below).

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

```bnf
    <call> ::= ID ( <args> )

    <args> ::= <arg-list> | empty

    <arg-list> ::= <arg-list> , <expression> | <expression>
```
</div>

A function call consists of an _**ID** _(the name of the function), followed by parentheses enclosing its arguments. Arguments are either empty or consist of a comma-separated list of expressions, representing the values to be assigned to parameters during a call. Functions must be declared before they are called, and the number of parameters in a declaration must equal the number of arguments in a call. An array parameter in a function declaration must be matched with an expression consisting of a single identifier representing an array variable.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Finally, the above rules give no input or output statement. We must include such functions in the definition of C-, since unlike C, C- has no separate compilation or linking facilities. We, therefore, consider two functions to be **predefined** in the global environment, as though they had the indicated declarations:

```c
    int input(void)  {...}

    void output(int x) {...}
```
</div>

The **input** function has no parameters and returns an integer value from the standard input device (usually the keyboard). The **output** function takes one integer parameter, whose value it prints to the standard output (usually the screen), together with a newline.


</div>

## Sample Programs

The following is a program that inputs two integers, computes their greatest common divisor, and prints it:

```c
    /* A program to perform Euclid's

       Algorithm to compute gcd. */

    int gcd (int u, int v)

    {

        if (v == 0) return u ;

        else return gcd(v,u-u/v*v);

        /* u-u/v*v == u mod v */

    }

    void main(void) 

    { 

       int x; int y;

       x = input(); 

       y = input();

       output(gcd(x, y)) ;

    }
```
</div>

The following is a program that inputs a list of 10 integers, sorts them by selection sort, and outputs them again:

```c
    /* A program to perform selection sort on a 10 element array */

    int x[10];

    int minloc(int a[], int low, int high) {

        int i; int x; int k;

        k = low;

        x = a[low];

        i = low + 1;

        while (i < high) {

            if (a[i] < x) {

                x = a[i];

                k = i;

            }

            i = i + 1;

        }

        return k;

    }

    void sort(int a[], int low, int high) {

        int i;

        int k;

        i = low;

        while (i < high - 1) {

            int t;

            k = minloc(a, i, high);

            t = a[k];

            a[k] = a[i];

            a[i] = t;

            i = i + 1;

        }

    }

    void main(void) {

        int i;

        i = 0;

        while (i < 10) {

            x[i] = input();

            i = i + 1;

        }

        sort(x, 0, 10);

        i = 0;

        while (i < 10) {

            output(x[i]);

            i = i + 1;

        }

    }
```

</div>

</div>

</div>

</div>

</div>

</div>

</div>

</div>

</div>

</section>