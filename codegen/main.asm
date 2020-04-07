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
# Running thru ordinal counter
# Local variable [b], stack_pos [0] 
# Local variable [x], stack_pos [1] 
# Local variable [c], stack_pos [5] 
# Running thru ordinal counter
# Local variable [d], stack_pos [6] 
# parameter [a0], position [7]
# parameter [a1], position [8]
	 # f() [0] params, [7] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 28 # push local vars
# {
# }
add $sp, $sp, 28 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
j $ra

_f_main:
	 # main() [0] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
# {
li  $t0, 3
sub $sp, $sp, 4
sw  $t0, ($sp)
li  $t1, 2
sub $sp, $sp, 4
sw  $t1, ($sp)
jal _f_f
move $t2 $v0
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
