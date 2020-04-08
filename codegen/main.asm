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
# Local variable [y], stack_pos [1] 
	 # main() [0] params, [2] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 8 # push local vars
move $fp, $sp
# {
li  $t0, 1
sw  $t0, 0($fp)
li  $t0, 2
sw  $t0, 4($fp)
lw  $t0, 0($fp)
lw  $t1, 4($fp)
sub $t2, $t0, $t1
sltu $t2, $zero, $t2
xori $t2, $t2, 1
bne $t2, $zero _L0
b _L1
_L0:
li  $t0, 1
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
b _L2
_L1:
li  $t0, 2
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
_L2:
li  $t0, 3
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 0($fp)
lw  $t1, 4($fp)
sub $t2, $t0, $t1
sltu $t2, $zero, $t2
bne $t2, $zero _L3
b _L4
_L3:
li  $t0, 4
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
b _L5
_L4:
li  $t0, 5
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
_L5:
li  $t0, 6
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 0($fp)
lw  $t1, 4($fp)
sub $t2, $t0, $t1
sltu $t2, $zero, $t2
xori $t2, $t2, 1
bne $t2, $zero _L6
b _L7
_L6:
li  $t0, 7
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
b _L8
_L7:
_L8:
li  $t0, 8
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
lw  $t0, 0($fp)
lw  $t1, 4($fp)
sub $t2, $t0, $t1
sltu $t2, $zero, $t2
bne $t2, $zero _L9
b _L10
_L9:
li  $t0, 9
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
b _L11
_L10:
_L11:
li  $t0, 10
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 8 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
move $fp, $sp
j $ra

main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
