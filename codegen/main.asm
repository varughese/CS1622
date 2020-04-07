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

_f_f:
# Local variable [b], stack_pos [0] 
# Local variable [x], stack_pos [1] 
# Local variable [c], stack_pos [5] 
# Local variable [d], stack_pos [6] 
# Local variable [d], stack_pos [7] 
# parameter [a0], position [8]
# parameter [a1], position [9]
	 # f() [2] params, [8] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 32 # push local vars
# {
li  $t0, 4
sw  $t0, 24($sp)
lw  $t0, 24($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t1 $v0
li  $t2, 4
sw  $t2, 0($sp)
li  $t2, 3
sw  $t2, 20($sp)
lw  $t2, 0($sp)
lw  $t3, 20($sp)
add $t4, $t2, $t3
sub $sp, $sp, 4
sw  $t4, ($sp)
jal _f_output
move $t2 $v0
# }
add $sp, $sp, 32 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 8 # pop arguments 
j $ra

_f_main:
	 # main() [0] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
# {
li  $t3, 3
sub $sp, $sp, 4
sw  $t3, ($sp)
li  $t5, 2
sub $sp, $sp, 4
sw  $t5, ($sp)
jal _f_f
move $t6 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
j $ra

main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
