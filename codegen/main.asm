_f_output:
sub $sp, $sp, 4
sw $ra, 0($sp)
lw $a0, 4($sp)li $v0, 1
syscall
li $v0, 11
li $a0, 0x0a
syscall

_f_main:
# push ra
sub $sp, $sp, 4
sw $ra, 0($sp)
# {
#local variable [x0]
lw $<> 4($sp)
# }
# pop ra
lw $ra, ($sp)
add $sp, $sp, 4
j $ra

# TODO - Turn ast into MIPS lol
main:
	jal _f_main
	li $v0, 10 # We need to do this syscall to exit
	syscall # Or else it will error!
