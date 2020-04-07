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

.data
garr: .word 0:15 

.text
_f_f:
# Local variable [b], stack_pos [0] 
# Local variable [x], stack_pos [1] 
# Local variable [c], stack_pos [5] 
# parameter [a0], position [6]
# parameter [a1], position [7]
	 # f() [2] params, [6] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 24 # push local vars
# {
lw  $t0, 28($sp)
lw  $t1, 32($sp)
add $t2, $t0, $t1
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 24 # pop local vars
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
li  $t1, 3
sub $sp, $sp, 4
sw  $t1, ($sp)
li  $t3, 2
sub $sp, $sp, 4
sw  $t3, ($sp)
jal _f_f
move $t4 $v0
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
