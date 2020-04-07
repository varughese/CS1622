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

_f_bar:
# parameter [a], position [0]
# parameter [b], position [1]
# parameter [c], position [2]
	 # bar() [3] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
move $fp, $sp
# {
lw  $t0, 4($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 8($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 12($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 12 # pop arguments 
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
lw  $t0, 12($fp)
li  $t1, 10
add $t2, $t0, $t1
sub $sp, $sp, 4
sw  $t2, ($sp)
lw  $t0, 8($fp)
li  $t1, 1
add $t2, $t0, $t1
sub $sp, $sp, 4
sw  $t2, ($sp)
lw  $t0, 4($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_bar
move $t0 $v0
lw  $t0, 8($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 12($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 12 # pop arguments 
move $fp, $sp
j $ra

_f_main:
# Local variable [c], stack_pos [0] 
# Local variable [cc], stack_pos [1] 
# Local variable [ccc], stack_pos [2] 
	 # main() [0] params, [3] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 12 # push local vars
move $fp, $sp
# {
li  $t0, 69
sw  $t0, 0($fp)
li  $t0, 6868
sw  $t0, 4($fp)
li  $t0, 676767
sw  $t0, 8($fp)
lw  $t0, 8($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
lw  $t0, 4($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
lw  $t0, 0($fp)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_foo
move $t0 $v0
lw  $t0, 0($fp)
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
