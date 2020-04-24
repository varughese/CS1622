# Optimization
Here are the optimizations we have created. We did them sort of quickly, so optimization is turned off by default.

To optimize, pass in a `-o` flag to the compiler. Example

```
./codegen main.c main.asm -o
```

1. We use all of the temporary registers. Instead of using the stack machine apporoach and having an accumulator, we instead use all temporary registers. Only in weird edge cases, like 

```c
x = 1+(2*(3+(4+(5+(6+(7+(8+(9+(10+(11+(12+(13+(14+(15+(16+(17+(18+(29+20))))))))))))))))))
```

So we do not need actually rely on the stack all the time.

2. Constant Folding
We constant fold.