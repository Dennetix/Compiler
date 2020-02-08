	.data
w_n:	.word 0
w_i:	.word 0
w_j:	.word 0
w_flag:	.word 0
	.text
	.globl main
main:
	li $a0 100
	sw $a0 w_n
	li $a0 2
	sw $a0 w_i
loop_start_3:
	li $a0 1
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_n
	lw $t1 0($sp)
	addiu $sp $sp 4
	addu $a0 $a0 $t1
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_i
	lw $t1 0($sp)
	addiu $sp $sp 4
	slt $a0 $a0 $t1
	beq $a0 1 lt_true_4
	li $a0 0
	b lt_end_4
lt_true_4:
	li $a0 1
lt_end_4:
	beq $a0 $zero loop_end_3
	li $a0 2
	sw $a0 w_j
	li $a0 0
	sw $a0 w_flag
loop_start_8:
	li $a0 1
	addiu $sp $sp -4
	sw $a0 0($sp)
	li $a0 2
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_i
	lw $t1 0($sp)
	addiu $sp $sp 4
	divu $a0 $a0 $t1
	lw $t1 0($sp)
	addiu $sp $sp 4
	addu $a0 $a0 $t1
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_j
	lw $t1 0($sp)
	addiu $sp $sp 4
	slt $a0 $a0 $t1
	beq $a0 1 lt_true_9
	li $a0 0
	b lt_end_9
lt_true_9:
	li $a0 1
lt_end_9:
	beq $a0 $zero loop_end_8
	li $a0 0
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_j
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_i
	lw $t1 0($sp)
	addiu $sp $sp 4
	divu $a0 $t1
	mfhi $a0
	lw $t1 0($sp)
	addiu $sp $sp 4
	beq $a0 $t1 equ_true_13
	li $a0 0
	b equ_end_13
equ_true_13:
	li $a0 1
equ_end_13:
	beq $a0 $zero con_end_12
	li $a0 1
	sw $a0 w_flag
con_end_12:
	li $a0 1
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_j
	lw $t1 0($sp)
	addiu $sp $sp 4
	addu $a0 $a0 $t1
	sw $a0 w_j
	b loop_start_8
loop_end_8:
	lw $a0 w_flag
	beq $a0 $zero lnot_true_19
	li $a0 0
	b lnot_end_19
lnot_true_19:
	li $a0 1
lnot_end_19:
	beq $a0 $zero con_end_18
	lw $a0 w_i
	li $v0 1
	syscall
	li $v0 11
	li $a0 10
	syscall
con_end_18:
	li $a0 1
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_i
	lw $t1 0($sp)
	addiu $sp $sp 4
	addu $a0 $a0 $t1
	sw $a0 w_i
	b loop_start_3
loop_end_3:
	jr $ra
