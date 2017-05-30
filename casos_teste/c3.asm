.text
.globl main

main:
	lw $t0, 0($sp)
	lw $t1, 0($sp)
loop:
	bne $t0, $t1, cont
	addiu $t0, $t0, 16
	addiu $t1, $t1, -16
	sll $t2, $t1, 2
cont:
	beq $zero, $t2, loop
	or $t2, $t1, $t2
	xori $t3, $t2, -1
	addu $s0, $t3, $t0
	j loop
loop2:
	j loop2
loop3:
	beq $zero, $t1, loop3
	beq $t1, $t2, loop2
	srl $s0, $s0, 1
	subu $s1, $s0, $s1
	andi $s1, $s1, 1
	andi $s1, $s1, -1
	j fim
	j main
fim:
	sltiu $s1, $s1, -4
	lui $s2, 4
	lui $a0, 0
	slt $s1, $s1, $s0
	sw $s0, 0($s0)
	sw $s1, 0($s0)
	j loop2
