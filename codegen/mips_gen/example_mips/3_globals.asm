# // Input
# int x;
# void function2(x) { output(x); }
# void main(void) { x = 4; function2(); }

.data
global_var: .word 5

.text
.globl main
_f_output:
	sub $sp, $sp, 4
	sw $ra, 0($sp)
	lw $a0, 4($sp)
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 0x0a
	syscall
	lw $ra, ($sp)
	add $sp, $sp, 4
	add $sp, $sp, 4
	j $ra


_f_function2:
	# push ra
	sub $sp, $sp, 4
	sw $ra, 0($sp)

	lw $a0, global_var
	sub $sp, $sp, 4
	sw $a0, 0($sp)
	jal _f_output

	# pop ra
	lw $ra, ($sp)
	add $sp, $sp, 4
	j $ra

_f_main:
	# push ra
	sub $sp, $sp, 4
	sw $ra, 0($sp)

	li $t0, 69
	sw $t0, global_var

	jal _f_function2

	# pop ra
	lw $ra, ($sp)
	add $sp, $sp, 4
	j $ra

main:
	jal _f_main
	li $v0, 10 # We need to do this syscall to exit
	syscall # Or else it will error!