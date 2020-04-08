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

_f_g:
# parameter [a], position [0]
# parameter [index], position [1]
	 # g() [2] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
move $fp, $sp
# {
lw  $t0, 4($fp)
lw  $t1, 8($fp)
sll $t1, $t1, 2
add $t0, $t0, $t1
lw  $t0, ($t0)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 8 # pop arguments 
move $fp, $sp
j $ra

_f_f:
# Local variable [x], stack_pos [0] 
# parameter [a], position [1]
	 # f() [1] params, [1] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 4 # push local vars
move $fp, $sp
# {
li  $t0, 99
lw  $t1, 8($fp)
sw  $t0, 12($t1)
li  $t0, 1
sw  $t0, 0($fp)
lw  $t0, 0($fp)
lw  $t1, 0($fp)
add $t2, $t0, $t1
lw  $t0, 0($fp)
add $t1, $t2, $t0
sub $sp, $sp, 4
sw  $t1, ($sp)
lw  $t0, 8($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_g
move $t0 $v0
# }
add $sp, $sp, 4 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 4 # pop arguments 
move $fp, $sp
j $ra

_f_main:
# Local variable [y], stack_pos [0] 
# Local variable [x], stack_pos [4] 
	 # main() [0] params, [5] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 20 # push local vars
move $fp, $sp
# {
li  $t0, 1
sw  $t0, 16($fp)
li  $t0, 102
la  $t1, 0($fp)
lw  $t2, 16($fp)
li  $t3, 1
add $t4, $t2, $t3
sll $t4, $t4, 2
add $t1, $t1, $t4
sw  $t0, ($t1)
la  $t0, 0($fp)
li  $t1, 1
li  $t2, 1
add $t3, $t1, $t2
sll $t3, $t3, 2
add $t0, $t0, $t3
lw  $t0, ($t0)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
la  $t0, 0($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_f
move $t0 $v0
# }
add $sp, $sp, 20 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
move $fp, $sp
j $ra

main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
