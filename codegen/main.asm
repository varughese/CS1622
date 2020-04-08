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
# Local variable [y], stack_pos [0] 
# Local variable [x], stack_pos [1] 
# Local variable [z], stack_pos [2] 
	 # main() [0] params, [3] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 12 # push local vars
move $fp, $sp
# {
li  $t0, 10
sw  $t0, 4($fp)
li  $t0, 20
sw  $t0, 0($fp)
lw  $t0, 0($fp)
lw  $t1, 4($fp)
mul $t2, $t0, $t1
sw  $t2, 8($fp)
lw  $t0, 8($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 0($fp)
li  $t1, 2
mul $t2, $t0, $t1
sw  $t2, 8($fp)
lw  $t0, 8($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 12 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
move $fp, $sp
j $ra

main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
