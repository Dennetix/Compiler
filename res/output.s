	.text
	.globl main
main:
	li $a0 100
	sw $a0 0($sp)
	addiu $sp $sp -4
	li $a0 2
	lw $t1 4($sp)
	addiu $sp $sp 4
	mul $a0 $a0 $t1
	sw $a0 0($sp)
	addiu $sp $sp -4
	li $a0 200
	lw $t1 4($sp)
	addiu $sp $sp 4
	sub $a0 $a0 $t1
	beq $a0 $zero lnot_true_1
	li $a0 0
	b lnot_end_1
lnot_true_1:
	li $a0 1
lnot_end_1:
	li $v0 1
	syscall
	li $v0 11
	li $a0 10
	syscall
	jr $ra
