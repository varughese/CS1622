# // Input
# int factorial(int n) {
# 	if (n == 1) return 1;

# 	return n * factorial(n-1);
# }
# void main(void) {
# 	int x;
# 	x = factorial(3)
# 	output(x)
# }


.data

.text

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

_f_factorial:
	# push ra
	sub $sp, $sp, 4
	sw $ra, 0($sp)
	
# {	

	# if ( ) { _if_body } _end_of_if_body

	# load arg from stack
	lw $a0, 4($sp)
	li $t0, 1
	bne $a0, $t0, _end_of_if_body
	_if_body:
		li $v0, 1
		b _f_factorial_return
	
	_end_of_if_body:

	sub $t0, $a0, 1

	# push s0
	sub $sp, $sp, 4
	sw $s0, 0($sp)

	# s0 = a0 
	move $s0, $a0

	# a0 = t0 [a0 -1]
	move $a0 $t0

	# factorial(a0)
	sub $sp, $sp, 4
	sw $a0, 0($sp)
	jal _f_factorial

	# v0 = s0 * v0
	mult	$s0, $v0
	mflo	$v0
	
	# pop s0
	lw $s0, 0($sp)
	add $sp, $sp, 4

# }

	_f_factorial_return:

	# pop $ra
	lw $ra, ($sp)
	add $sp, $sp, 4

	# pop args
	add $sp, $sp, 4
	j $ra

_f_main:
	# push ra
	sub $sp, $sp, 4
	sw $ra, 0($sp)
	
# {

	# a0 = 4
	li $a0, 4
	
	# v0 = factorial(a0) 
	sub $sp, $sp, 4
	sw $a0, 0($sp)
	jal _f_factorial

	# a0 = v0 [ =factorial(4) ]
	move $a0, $v0

	# output(a0)
	sub $sp, $sp, 4
	sw $a0, 0($sp)
	jal _f_output

# }

	# pop $ra
	lw $ra, ($sp)
	add $sp, $sp, 4
	j $ra

main:
	jal _f_main
	li $v0, 10 # We need to do this syscall to exit
	syscall # Or else it will error!


#############################################
#### NOTES ##################################
#############################################

# The following is just some notes from this:

# Every file ends with the same main label

# Convert main() {} to _f_main

# Every function starts with
# push ra
	sub $sp, $sp, 4
	sw $ra, 0($sp)
# // { CODE }
# pop $ra
	lw $ra, ($sp)
	add $sp, $sp, 4
	j $ra

# When you call a function, load args into stack
	sub $sp, $sp, 4
	sw $a0, 0($sp)
	jal _f_function_name

# When you start a function, load arg from stack
	lw $a0, 4($sp)
	# parameter_i = 4*i+4 ($sp)

# When you end a function, clean the arguments
	add $sp, $sp, 4
	# for each parameter

# Every function should have a section for return label
#   that gets branch'd too whenever there is a return
	_f_function_name_return: