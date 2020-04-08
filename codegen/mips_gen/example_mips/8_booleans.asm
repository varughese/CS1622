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
	li $v0, 1
	syscall

	li $v0, 11
	li $a0, 0x0a
	syscall
	j $ra

_f_main:
	# push ra
	sub $sp, $sp, 4
	sw $ra, 0($sp)
	
# {

	# s0 RELOP s1
	li $s0, 14
	li $s1, 13

	# ==
	sub $t1, $s0, $s1
	# Set $t1 to 1 if it's non-zero
	sltu $t1, $zero, $t1
	# Flip the lsb so that 0 becomes 1, and 1 becomes 0
	xori $t1, $t1, 1

	# !=
	sub $t1, $s0, $s1
	# Set $t1 to 1 if it's non-zero
	sltu $t1, $zero, $t1
	
	# > =
	sub $t1, $s1, $s0
	slti $t1, $t1, 1

	# >
	sub $t1, $s1, $s0
	slt $t1, $t1, $zero

	# < =
	sub $t1, $s0, $s1
	slti $t1, $t1, 1

	# <
	sub $t1, $s0, $s1
	slt $t1, $t1, $zero

	move $a0 $t1
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