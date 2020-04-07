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
_f_main:
# Local variable [x], stack_pos [0] 
# Local variable [x], stack_pos [30] 
# Local variable [y], stack_pos [40] 
	 # main() [0] params, [240] local vars
sub $sp, $sp, 4 # push ra
sw  $ra, 0($sp)
sub $sp, $sp, 960 # push local vars
# {
li  $t0, 6000
la  $t1, 0($sp)
sw  $t0, 24($t1)
li  $t0, 100
la  $t1, garr
sw  $t0, 4($t1)
li  $t0, 300
la  $t1, garr
sw  $t0, 12($t1)
la  $t0, garr
lw  $t0, 4($t0)
sub $sp, $sp, 4
sw  $t0, ($sp)
jal _f_output
move $t0 $v0
la  $t1, garr
lw  $t1, 12($t1)
sub $sp, $sp, 4
sw  $t1, ($sp)
jal _f_output
move $t1 $v0
la  $t2, 0($sp)
lw  $t2, 24($t2)
sub $sp, $sp, 4
sw  $t2, ($sp)
jal _f_output
move $t2 $v0
li  $t3, 60000
la  $t4, 120($sp)
sw  $t3, 24($t4)
li  $t3, 40000
la  $t4, 160($sp)
sw  $t3, 16($t4)
la  $t3, 120($sp)
lw  $t3, 24($t3)
sub $sp, $sp, 4
sw  $t3, ($sp)
jal _f_output
move $t3 $v0
la  $t4, 160($sp)
lw  $t4, 16($t4)
sub $sp, $sp, 4
sw  $t4, ($sp)
jal _f_output
move $t4 $v0
# }
add $sp, $sp, 960 # pop local vars
lw  $ra, ($sp)
add $sp, $sp, 4
add $sp, $sp, 0 # pop arguments 
j $ra

main:
jal _f_main
li $v0, 10 # We need to do this syscall to exit
syscall # Or else it will error!
