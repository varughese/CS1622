# CS 1622 C- Compiler
By Mathew Varughese & Ming Wang

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

## 4. Code Generation
Coming soon
