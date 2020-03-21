# Part II: Syntactic Analysis
In this part of the project, we implemented the phase of syntactic analysis for the Cminus language, including the construction of the Abstract Syntactic Tree (AST). The parser will read in a source file (in Cminus) and determines whether or not the program follows the language grammar specification, and in case of success it generates the AST as output.

The book "Introduction to Compilers and Language Design" by Douglas Thain was very helpful.

Especially
[Chapter 5 – Parsing in Practice](https://www.google.com/url?q=https%3A%2F%2Fwww3.nd.edu%2F~dthain%2Fcompilerbook%2Fchapter5.pdf&sa=D&sntz=1&usg=AFQjCNGTEf8Mh3ghksofI_iEITThmm8uFQ)
[Chapter 6 – The Abstract Syntax Tree](https://www.google.com/url?q=https%3A%2F%2Fwww3.nd.edu%2F~dthain%2Fcompilerbook%2Fchapter6.pdf&sa=D&sntz=1&usg=AFQjCNHMdtB4VinROmegjXsIBWi2s7uGrg)

This material was a helpful intro to Bison: [Intro to Bison](https://www.google.com/url?q=https%3A%2F%2Fwww.dropbox.com%2Fs%2F0fbivxcwi20tpyb%2F120%2520Introducing%2520bison.pdf&sa=D&sntz=1&usg=AFQjCNHhGLYT9NKlTc_fxns3qkbcFWqDoQ)


**How to run it (using two arguments: input and output)**

The program must read input from a file (source) and write output to another file (target). In case of syntactic error, the contents of the output file must be empty (0 bytes).

```
$ ./parser main.c main.ast
```

**Example of input file (main.c)**
```c
int g;

int foo(int x, int y, int z[])
{
    z[0] = 0;
    y = x * y + 2;

    if(y == 0)
    {
        y = 1;
    }

    return y;
}

void main(void)
{
    int a[10];
    while(g < 10)
    {
        g = foo(g, 2, a);
        ;
    }
}
```

**Example of output file (main.ast)**
Important: You do not have to worry about whitespaces in the output file, they will be ignored during the auto-grading process.

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