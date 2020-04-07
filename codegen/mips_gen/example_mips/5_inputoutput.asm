# Run with:
# spim -file 5_inputoutput.asm < input.stdin > output.stdout

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

_f_input:
	li  $v0, 5
	syscall
	j $ra

main:
	# this quick version of main, generated would look different

	# v0 = input()
	jal _f_input
	
	addi $a0, $v0, 1
	sub $sp, $sp, 4
	sw $a0, 0($sp)
	jal _f_output

	# v0 = input()
	jal _f_input
	sw $v0, 0($sp)
	jal _f_output

	li $v0, 10 # We need to do this syscall to exit
	syscall # Or else it will error!