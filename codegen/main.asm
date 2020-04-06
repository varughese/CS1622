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

_f_input:
li  $v0, 5
syscall
j $ra

_f_main:
	 # main() [0] params, [1] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 4 # push local vars
# {
# declare local variable [x0], pos [0] 
jal _f_input
move $t0 $v0
sw  $t0, 0($sp)
lw  $t1, 0($sp)
sub $sp, $sp, 4
sw  $t1, ($sp)
jal _f_output
move $t2 $v0
# }
add $sp, $sp, 4 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
j $ra


# TODO - Turn ast into MIPS lol
main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
