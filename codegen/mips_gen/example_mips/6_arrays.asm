# // Input
# int garr[15];
# void f(int a0, int a1) {
# 	int b; 
# 	int x[4]; 
#	int c;
# }
# void main(void) {
#	f(1,2);
# }


.data
.word garr 715:15

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

_f_main:
	# push ra
	sub $sp, $sp, 4
	sw $ra, 0($sp)
	
	# allocate b
	sub $sp, $sp, 4
	# allocate x
	sub $sp, $sp, 4
	# allocate a

	# We see that we have an array,
	#	this is a special case. We reserver
	#	spots on the stack for this
	# store int x[10];
	sub $sp, $sp, 4*10

# {

	

# }

	# pop $ra
	lw $ra, ($sp)
	add $sp, $sp, 4
	j $ra

main:
	jal _f_main
	li $v0, 10 # We need to do this syscall to exit
	syscall # Or else it will error!