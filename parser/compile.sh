bison --defines=token.h --output=parser.c parser.bison
gcc -o parser parser.c 