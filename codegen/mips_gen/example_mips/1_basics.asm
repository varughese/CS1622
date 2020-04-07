# // Input
# void main(void) { output(4+5) }

.data

.text

_f_output:
	# push ra
	sub $sp, $sp, 4
	sw $ra, 0($sp)

		# STACK [ra, 9, ra]
	# {

	# load arg from stack
	lw $a0, 4($sp)

	# print a0 and '\n'
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 0x0a
	syscall

	# }

	# pop ra
	lw $ra, ($sp)
	add $sp, $sp, 4

		# STACK [9, ra]

	# pop args
	add $sp, $sp, 4

		# STACK [ra]

	j $ra

_f_main:
	# push ra
	sub $sp, $sp, 4
	sw $ra, 0($sp)
	
		# STACK [ra]

	# {

	# a0 = 9
	li $t0 4
	li $t1 5
	add $a0, $t0, $t1
	
	# push a0, 
	#	(do this to save params on stack before calling)
	sub $sp, $sp, 4
	sw $a0, 0($sp)

		# STACK [9, ra]

	# output(a0)
	jal _f_output

		# STACK [ra]

	# }

	# pop $ra
	lw $ra, ($sp)
	addi $sp, $sp, 4
	j $ra

main:
	jal _f_main
	li $v0, 10 # We need to do this syscall to exit
	syscall # Or else it will error!