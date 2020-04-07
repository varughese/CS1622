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
_f_foo:
# parameter [a], position [0]
# parameter [a1], position [1]
	 # foo() [2] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
# {
la  $t0, 4($sp)
lw  $t0, 4($t0)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 8 # pop arguments 
j $ra

_f_food:
# parameter [a], position [0]
	 # food() [1] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
# {
lw  $t0, 4($sp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 4 # pop arguments 
j $ra

_f_main:
# Local variable [y], stack_pos [0] 
	 # main() [0] params, [4] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 16 # push local vars
# {
li  $t0, 102
la  $t1, 0($sp)
sw  $t0, 0($t1)
li  $t0, 103
la  $t1, 0($sp)
sw  $t0, 4($t1)
li  $t0, 104
la  $t1, 0($sp)
sw  $t0, 8($t1)
li  $t0, 105
la  $t1, 0($sp)
sw  $t0, 12($t1)

#a1
li  $t0, 4
sub $sp, $sp, 4
sw  $t0, ($sp)
#a0
la  $t0, 4($sp)

sub $sp, $sp, 4
sw  $t0, ($sp)

jal _f_foo
move $t0 $v0
# }
add $sp, $sp, 16 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
j $ra

main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
