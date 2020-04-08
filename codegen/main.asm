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
# Local variable [x], stack_pos [0] 
	 # main() [0] params, [1] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 4 # push local vars
move $fp, $sp
# {
li  $t0, 0
li  $t1, 1
sub $t2, $t0, $t1
sltu $t2, $zero, $t2
xori $t2, $t2, 1
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 1
li  $t1, 1
sub $t2, $t0, $t1
sltu $t2, $zero, $t2
xori $t2, $t2, 1
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 1
li  $t1, 1
sub $t2, $t0, $t1
sltu $t2, $zero, $t2
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 0
li  $t1, 1
sub $t2, $t0, $t1
sltu $t2, $zero, $t2
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 111
li  $t1, 1
sub $t2, $t0, $t1
slti $t2, $t2, 1
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 1
li  $t1, 1
sub $t2, $t0, $t1
slti $t2, $t2, 1
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 1
li  $t1, 1
sub $t2, $t0, $t1
slt $t2, $t2, $zero
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 1
li  $t1, 11
sub $t2, $t0, $t1
slt $t2, $t2, $zero
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 1
li  $t1, 1
sub $t2, $t1, $t0
slt $t2, $t2, $zero
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 11
li  $t1, 1
sub $t2, $t1, $t0
slt $t2, $t2, $zero
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 1
li  $t1, 11
sub $t2, $t1, $t0
slti $t2, $t2, 1
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
li  $t0, 1
li  $t1, 1
sub $t2, $t1, $t0
slti $t2, $t2, 1
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 4 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
move $fp, $sp
j $ra

main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
