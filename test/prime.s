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
loop_1:
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
	beq $a0 1 lt_2
	li $a0 0
	b end_lt_2
lt_2:
	li $a0 1
end_lt_2:
	beq $a0 $zero end_loop_1
	li $a0 2
	sw $a0 w_j
	li $a0 0
	sw $a0 w_flag
loop_3:
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
	beq $a0 1 lt_4
	li $a0 0
	b end_lt_4
lt_4:
	li $a0 1
end_lt_4:
	beq $a0 $zero end_loop_3
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
	beq $a0 $t1 equ_5
	li $a0 0
	b end_equ_5
equ_5:
	li $a0 1
end_equ_5:
	beq $a0 $zero end_con_6
	li $a0 1
	sw $a0 w_flag
end_con_6:
	li $a0 1
	addiu $sp $sp -4
	sw $a0 0($sp)
	lw $a0 w_j
	lw $t1 0($sp)
	addiu $sp $sp 4
	addu $a0 $a0 $t1
	sw $a0 w_j
	b loop_3
end_loop_3:
	lw $a0 w_flag
	beq $a0 $zero lnot_7
	li $a0 0
	b end_lnot_7
lnot_7:
	li $a0 1
end_lnot_7:
	beq $a0 $zero end_con_8
	lw $a0 w_i
	li $v0 1
	syscall
	li $v0 11
	li $a0 10
	syscall
end_con_8:
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
