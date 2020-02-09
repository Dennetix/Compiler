	.data
w_t2:	.word 0
w_i:	.word 0
w_t1:	.word 0
w_next:	.word 0
	.text
	.globl main
main:
	li $a0 1
	sw $a0 w_t2
loop_1:
	li $a0 45
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_i
	lw $t1 0($sp)
	addiu $sp $sp 4
	slt $a0 $a0 $t1
	beq $a0 1 lt_2
	li $a0 0
	b end_lt_2
lt_2:
	li $a0 1
end_lt_2:
	beq $a0 $zero end_loop_1
	lw $a0 w_t1
	li $v0 1
	syscall
	li $v0 11
	li $a0 10
	syscall
	lw $a0 w_t2
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_t1
	lw $t1 0($sp)
	addiu $sp $sp 4
	addu $a0 $a0 $t1
	sw $a0 w_next
	lw $a0 w_t2
	sw $a0 w_t1
	lw $a0 w_next
	sw $a0 w_t2
	li $a0 1
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_i
	lw $t1 0($sp)
	addiu $sp $sp 4
	addu $a0 $a0 $t1
	sw $a0 w_i
	b loop_1
end_loop_1:
	jr $ra
