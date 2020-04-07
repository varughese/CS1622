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
g: .word 0

.text
.data
garr: .word 0:4 

.text
_f_bar:
# parameter [a], position [0]
# parameter [b], position [1]
# parameter [c], position [2]
# parameter [d], position [3]
	 # bar() [4] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
move $fp, $sp
# {
# Symbol is an array param. Load the pointer.
lw  $t0, 4($fp)
lw  $t0, 4($t0)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 16 # pop arguments 
move $fp, $sp
j $ra

_f_foo:
# parameter [a], position [0]
# parameter [b], position [1]
# parameter [c], position [2]
	 # foo() [3] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
move $fp, $sp
# {
# Symbol is an array param. Load the pointer.
lw  $t0, 4($fp)
lw  $t0, 4($t0)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 12($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
lw  $t0, 8($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
# Symbol is an array param. Load the pointer.
lw  $t0, 4($fp)
lw  $t0, 4($t0)
sub $sp, $sp, 4
sw  $t0, ($sp)
lw  $t0, 4($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_bar
move $t0 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 12 # pop arguments 
move $fp, $sp
j $ra

_f_main:
# Local variable [x], stack_pos [0] 
# Local variable [y], stack_pos [1] 
	 # main() [0] params, [5] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 20 # push local vars
move $fp, $sp
# {
li  $t0, 101
sw  $t0, 0($fp)
li  $t0, 102
la  $t1, 4($fp)
sw  $t0, 0($t1)
li  $t0, 103
la  $t1, 4($fp)
sw  $t0, 4($t1)
li  $t0, 104
la  $t1, 4($fp)
sw  $t0, 8($t1)
li  $t0, 105
la  $t1, 4($fp)
sw  $t0, 12($t1)
la  $t0, 4($fp)
lw  $t0, 12($t0)
sub $sp, $sp, 4
sw  $t0, ($sp)
lw  $t0, 0($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
la  $t0, 4($fp) # fuck
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_foo
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
