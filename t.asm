.text

.globl main
main:

        addiu      $s0, $zero, 12
        lw      $s0, 0($s0)


        addiu      $s1, $zero, 7
        lw      $s1, 0($s1)


        subu     $s2, $s2, $s2

        addiu      $t0, $zero, 1


loop:
        beq     $s1,$zero, fim

        andi     $t1,$s1,1

        bne     $t1,$zero, soma

volta:
        srl     $s1,$s1,1
        sll     $s0,$s0,1

        j       loop

soma:
	addu    $s2, $s2, $s0
        j       volta

fim:
        sw      $s2, 0($t0)

aqui:
        j       aqui
