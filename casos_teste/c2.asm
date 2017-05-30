.text
.globl main

main:
    addiu $t0, $zero, 23
    addiu $t1, $zero, 23
    addu $t0, $t0, $t1

    xori  $t0, $t0, 2
    subu $t1, $t1, $t0
    addiu $t1, $zero, 5
    subu $t0, $t0, $t1

    lui $t1, 4
    sltiu $t2, $t1, 10
    andi $t2, $t2, -3

    addiu $sp, $sp, -8
    sw $t1, 4($sp)
    sw $t2, 0($sp)
    bne $t1, $t2, l1
    j f
l1:
    lw $t3, 4($sp)
    lw $t4, 0($sp)
    or $t0, $t1, $t2
    slt $t0, $t2, $t0
    sll $t0, $t0, 2
    srl $t1, $t1, 2
    beq $t0, $t1, main
    j f
f:
    j f
