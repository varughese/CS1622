I am just trying to remember MIPS in this folder.

https://www.dsi.unive.it/~arcb/LAB/spim.htm

## CPU Registers
| Register Name 	| #  	|   	| Usage                                   	|
|---------------	|----	|---	|-----------------------------------------	|
| zero          	| 0  	|   	| Constant 0                              	|
| at            	| 1  	|   	| Reserved for assembler                  	|
| v0            	| 2  	|   	| Expression evaluation and               	|
| v1            	| 3  	|   	| results of a function                   	|
| a0            	| 4  	|   	| Argument 1                              	|
| a1            	| 5  	|   	| Argument 2                              	|
| a2            	| 6  	|   	| Argument 3                              	|
| a3            	| 7  	|   	| Argument 4                              	|
| t0            	| 8  	|   	| Temporary (not preserved across call)   	|
| t1            	| 9  	|   	| Temporary (not preserved across call)   	|
| t2            	| 10 	|   	| Temporary (not preserved across call)   	|
| t3            	| 11 	|   	| Temporary (not preserved across call)   	|
| t4            	| 12 	|   	| Temporary (not preserved across call)   	|
| t5            	| 13 	|   	| Temporary (not preserved across call)   	|
| t6            	| 14 	|   	| Temporary (not preserved across call)   	|
| t7            	| 15 	|   	| Temporary (not preserved across call)   	|
| s0            	| 16 	|   	| Saved temporary (preserved across call) 	|
| s1            	| 17 	|   	| Saved temporary (preserved across call) 	|
| s2            	| 18 	|   	| Saved temporary (preserved across call) 	|
| s3            	| 19 	|   	| Saved temporary (preserved across call) 	|
| s4            	| 20 	|   	| Saved temporary (preserved across call) 	|
| s5            	| 21 	|   	| Saved temporary (preserved across call) 	|
| s6            	| 22 	|   	| Saved temporary (preserved across call) 	|
| s7            	| 23 	|   	| Saved temporary (preserved across call) 	|
| t8            	| 24 	|   	| Temporary (not preserved across call)   	|
| t9            	| 25 	|   	| Temporary (not preserved across call)   	|
| k0            	| 26 	|   	| Reserved for OS kernel                  	|
| k1            	| 27 	|   	| Reserved for OS kernel                  	|
| gp            	| 28 	|   	| Pointer to global area                  	|
| sp            	| 29 	|   	| Stack pointer                           	|
| fp            	| 30 	|   	| Frame pointer                           	|
| ra            	| 31 	|   	| Return address (used by function call)  	|

## MIPS Instructions

http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html

### Math
Add
```mips
# Addition (Overflow)
add Rdest, Rsrc1, Src2	

# Addition Immediate (Overflow)
addi Rdest, Rsrc1, Imm

# Addition (NO overflow)
addu Rdest, Rsrc1, Src2

# Addition Immediate (NO overflow)
addiu Rdest, Rsrc1, Imm
```

Mul
```mips
mul register_dest, Rsrc1, Scr2
```



### Load and Store

Load Address into register
```mips
la $t0, address
```

Also `lb`, and `lbu` (and then byte, and half word)


Load Word into register 
Like doing `$t0 = *address`
```mips
lw $t0, address
```

Store word - contents of $t0 stored at the address
```mips
sw $t0, offset($s0)
```

Store Address from register to memory
```mips
sb register_source, address
```

### Syscall
[Source](https://www.doc.ic.ac.uk/lab/secondyear/spim/node8.html)

Print Int
```mips
li $v0, 9
li $a0, 4
syscall # Print `9`
```

Read Int
```mips
li $a0, 5
syscall # Get user input
```

Ask for memory (malloc an array)
```mips
li $a0, 8 # 8 bytes, so 2 ints
li $v0, 9
syscall # Increase sbrk by 9
v0 # v0 now has the address, like malloc
```

### Comparisions

```python
a0 = 1 if v0 == v1 else 0

seq $a0, $v0, $v1
```

```python
a0 = 1 if v0 > v1 else 0

sge $a0, $v0, $v1
```

```
sgeu
sgt
sgtu (unsigned)
sle
sleu (unsigned)
slt 
slti (imm)
sltu (unsigned)
sltiu (unsigned imm)
```

### Branch
```
b label
```

`if (t0 == t1) GOTO label`
```mips
beq $t0, $t1, label
```

```
bge
bgt

ble
blg
```

## Calling Convention
A **frame** is the memory between `$fp` and `$sp`

`$fp` - point to word immediately after last argument passed on the stack

`$sp` - points to first free word on stack

Stack grows down.

**To make a call**
1. Pass the args in `$a0 ... $a3`
2. `jal`

**In the routine**
1. Establish stack frame. Subtract frame size from `$sp`
2. Save `$ra`

**Return call**
1. Restore any callee saved across call
2. Pop stack frame (subtract frame size from `$sp`)
3. Return to address in `$ra`


## Stack and Variables Example
The stack seems scary, but it really is not that bad after staring at it for 30 minutes.
```c
void f(int a0, int a1) {
	int x;
	int y;
	int z;
}

void main() {
	f(100, 200);
}
```

So in this example, `main` calls `f` with the two arguments `100` and `200`. Before main calls `f`, it puts those values on the stack. `f` then puts the $ra onto the stack. Then, it allocates memory for its 3 local variables on the stack. So, the stack looks like:

```
100 # a1
200 # a0
$ra
x
y
z		<- $sp
```

In the compiler, each symbol has a `which` variable to indicate the position it is located.
In mips_gen, we call `increase_param_symbol_which` to increase the `which` of the arguments.

```
a1->which	4	20 ($sp)
a0->which	3	16 ($sp)
// 				12 ($sp) contains $ra
z->which	2	8 ($sp)
y->which	1	4 ($sp)
x->which	0	0 ($sp)
```

So, for local variables, we can just do `<which * 4> $sp`.

For parameters, we can do `<which * 4 + 4> $sp`. We need to do the +4 to account for the $ra spot.