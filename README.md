# CS 1622 C- Compiler
By Mathew Varughese & Ming Wang

[![Build Status](https://travis-ci.com/varughese/CS1622.svg?token=ycDVMyxyCzpQECLefYzY&branch=master)](https://travis-ci.com/varughese/CS1622)

This is a project apart of `CS 1622` at Pitt taken the Spring '20 semester. The project is broken up into four parts which are put in their own folders. The lexical analysis, syntatic analysis, semantic analysis, and code generation.

The C- language is a subset of C, and more specifications can be read [here](https://github.com/varughese/CS1622/blob/master/docs/CMinus_Lang_Specification.md).

### *Read how the Abstract Syntax Tree is structured [here](https://github.com/varughese/CS1622/blob/master/docs/how_ast_structred.md). This is the key data structure used in compilation.*

## 1. Lexical Analysis
Uses `flex` to find the tokens in a file.

**Input**
```c
void main(void)
{
  int a;
  a = 4 + 5;
}
```

**Output**
```c
(1,KEY,"void")
(1,ID,"main")
(1,SYM,"(")
(1,KEY,"void")
(1,SYM,")")
(2,SYM,"{")
(3,KEY,"int")
(3,ID,"a")
(3,SYM,";")
(4,ID,"a")
(4,SYM,"=")
(4,NUM,"4")
(4,SYM,"+")
(4,NUM,"5")
(4,SYM,";")
(5,SYM,"}")
```

## 2. Syntatic Analysis
Using a BNF grammar and `bison`, convert the tokens into a abstract syntax tree that we define.

**Input**
```c
int g;

int foo(int x, int y, int z[]) {
    z[0] = 0;
    y = x * y + 2;
    
    if(y == 0) {
        y = 1;
    }

    return y;
}

void main(void) {
    int a[10];
    while(g < 10)
    {
        g = foo(g, 2, a);
        ;
    }
}
```

**Output**
This is a stringified version of the tree. Read how it is structured [here](https://github.com/varughese/CS1622/blob/master/docs/how_ast_structred.md).
```
[program 
  [var-declaration [int] [g]]
  [fun-declaration 
    [int]
    [foo]
    [params 
      [param [int] [x]] 
      [param [int] [y]] 
      [param [int] [z] [\[\]]]]
    [compound-stmt 
      [= [var [z] [0]] [0]]
      [= [var [y]] 
        [+ 
          [* [var [x]] [var [y]]] [2]]]
      [selection-stmt 
        [== [var [y]] [0]]
        [compound-stmt 
          [= [var [y]] [1]]
        ]
      ]
      [return-stmt [var [y]]]
    ]
  ]
  [fun-declaration 
    [void]
    [main]
    [params]
    [compound-stmt 
      [var-declaration [int] [a] [10]]
      [iteration-stmt 
        [< [var [g]] [10]]
        [compound-stmt 
          [= [var [g]] 
            [call
              [foo]
              [args [var [g]] [2] [var [a]]]
            ]]
          [;]
        ]
      ]
    ]
  ]
]
```

## 3. Semantic Analysis
Perform typechecking on the abstract syntax tree.
  - Are all variables assigned to the correct type?
  - Is there a main function?
  - Are all functions called with the right number of arguments?
  - Etc ...

## 4. Code Generation
Recurse through the AST, and piece by piece turn it into MIPS assembly code. Example output for the input 
code from part 1.

```mips
.text
_f_main:
# Local variable [a], stack_pos [0] 
# main() [0] params, [1] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 4 # push local vars
move $fp, $sp
# {
li  $t0, 4
li  $t1, 5
add $t2, $t0, $t1
sw  $t2, 0($fp)
_return_main:
# }
add $sp, $sp, 4 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
move $fp, $sp
j $ra

main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
```