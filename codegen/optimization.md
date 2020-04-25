# Optimization
Here are the optimizations we have created. Mainly, we added constant folding.

To optimize, pass in a `-o` flag to the compiler. Example

```
make
./codegen main.c main.asm -o
```

1. We use all of the temporary registers. Instead of using the stack machine apporoach and storing everything on stack, we pick and store registers on the AST (as described in the Notre Dame compilers book)and free them as we use them. This reduces uneccesary loads and stores significantly. Only in weird edge cases, like this:

```c
x = 1+(2*(3+(4+(5+(6+(7+(8+(9+(10+(11+(12+(13+(14+(15+(16+(17+(18+(29+20))))))))))))))))))
```

Do we run out of temporary registers and need to store values on the stack.

2. Constant Folding
We constant fold in `mips_gen/optimize.c` This is fairly straight forward. To test this, we ran the above program, and can see in the generated assembly that it folds the assembly. This saves a lot of wasted arithmetic exections.

We created a python test script in `test.py` that tests things for us. This file has evolved throughout the lifecycle of the compiler, but essentially, it runs test cases, passes them into the compiler, and then compares the expected vs actual output. We used this to ensure our optimizations did not break anything.