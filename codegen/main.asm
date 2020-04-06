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
g: .word 622 # Globals are not initialized in C-, so we put Mings bday. 

.text
_f_j:
# parameter [y], position [0]
	 # j() [1] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
# {
lw  $t0, 4($sp)
lw  $t1, g
add $t2, $t0, $t1
li  $t0, 69
add $t1, $t2, $t0
sub $sp, $sp, 4
sw  $t1, ($sp)
jal _f_output
move $t0 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 4 # pop arguments 
j $ra

_f_f:
# parameter [x], position [0]
	 # f() [1] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
# {
li  $t2, 4
sw  $t2, g
li  $t2, 9
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_j
move $t3 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 4 # pop arguments 
j $ra

_f_main:
	 # main() [0] params, [0] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 0 # push local vars
# {
li  $t4, 3
sub $sp, $sp, 4
sw  $t4, ($sp)
jal _f_f
move $t5 $v0
# }
add $sp, $sp, 0 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
j $ra


# TODO - Turn ast into MIPS lol
main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
