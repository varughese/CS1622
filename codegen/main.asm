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

_f_foo:
# parameter [a], position [0]
# parameter [b], position [1]
# parameter [c], position [2]
# parameter [d], position [3]
	 # foo() [4] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
# {
lw  $t0, 4($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 8($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 12($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 16($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 16 # pop arguments 
j $ra

_f_main:
# Local variable [y], stack_pos [0] 
# Local variable [c], stack_pos [4] 
# Local variable [cc], stack_pos [5] 
# Local variable [ccc], stack_pos [6] 
# Local variable [cccc], stack_pos [7] 
	 # main() [0] params, [8] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 32 # push local vars
# {
li  $t0, 1
sw  $t0, 16($sp)
li  $t0, 2
sw  $t0, 20($sp)
li  $t0, 3
sw  $t0, 24($sp)
li  $t0, 4
sw  $t0, 28($sp)
lw  $t0, 28($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
lw  $t0, 24($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
lw  $t0, 20($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
lw  $t0, 16($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_foo
move $t0 $v0
# }
add $sp, $sp, 32 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
j $ra

main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
