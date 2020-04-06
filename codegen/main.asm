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

_f_f:
	 # f() [2] params, [3] local vars
sub $sp, $sp, 4
sw $ra, 0($sp)
sub $sp, $sp, 12
# {
# declare local variable [x], pos [0] 
# declare local variable [y], pos [1] 
# declare local variable [z], pos [2] 
# }
add $sp, $sp, 12 # Pop local vars
lw $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 8 # Pop arguments 
j $ra

_f_main:
	 # main() [0] params, [1] local vars
sub $sp, $sp, 4
sw $ra, 0($sp)
sub $sp, $sp, 4
# {
# declare local variable [x0], pos [0] 
li $t0, 696969
sw $t0 0($sp)
# }
add $sp, $sp, 4 # Pop local vars
lw $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # Pop arguments 
j $ra


# TODO - Turn ast into MIPS lol
main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
