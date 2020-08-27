.name "all opcode"
.comment "Test of all the combinaison of opcode + aguments"

# Attention ADV affiche le champ d'adresse de la position (p->i) a la fin des arguments + 1
# exemple:
#P    1 | ld 68289282 r2
#ADV 5 (0x0000 -> 0x0005) 02 d0 00 07 02
#                  _/\_
#P    1 | ld 67083268 r3
#ADV 5 (0x0005 -> 0x000a) 02 d0 04 12 03
#        _/\_

# Dans le cas de store (st), si 2 registres sont passés en arguments alors la verbose opcode
# affiche un seul 'r':
# exemple:
# fichier.s : st r1, r5 donne:
# P    1 | st r1 5
# ADV 4 (0x0021 -> 0x0025) 03 50 01 05

# Pour add et sub combinaison unique : reg reg reg
# La verbose donne toujours : P      x | r1  r2  r3
#

# Pour un opcode or avec arguments (reg , reg, reg)
#		-> P    1 | or 48 68289282 r8
#		 On affiche le contenue des 2 premiers registres


# Les arguments IND sont TOUJOURS affichés en RELATIF dans la verbose

# Pour l'affichage des REG dans la verbose, on écrit le numéro du REG dans la plupart des
# opcodes mais pas tous.
# Liste des opcodes où les REG sont écrit en RELATIF:
#		LLDI, OR, XOR, AND	(RELATIF, RELATIF, ABSOLU)
#		LDI					(RELATIF, RELATIF, ABSOLU)
#		STI					(ABSOLU, RELATIF, RELATIF)
# Toutes les autre opérations sont en ABSOLU




ld 7, r2
ld 1042, r3
ld %-42, r4
aff r5
ld %48, r1
aff r1
aff r5
st r1, r5
st r1, r6
aff r5
st r3, -100
add r1, r2, r6
sub r1, r2, r7
or r1, r2, r8
or %-1, r3, r9
or %0, r2, r10
or 4, r2, r11
or 7, -4, r12
or %3, %1, r13
or %3, 1, r14
xor r1, r2, r8
xor %-1, r3, r9
xor %0, r2, r10
xor 4, r2, r11
xor 7, -4, r12
xor %3, %1, r13
xor %3, 1, r14
and r1, r2, r8
and %-1, r3, r9
and %0, r2, r10
and 4, r2, r11
and 7, -4, r12
and %3, %1, r13
and %3, 1, r14
ldi r1, r2, r15
ldi -1025, %604, r16
ldi -1025, r3, r2
sti r3, %4096, %655
sti r4, r6, r7
sti r5, %-60, r8
lld %780, r7
lld 4200, r7
lldi r10, r15, r16
lldi %675, %21, r11
lldi 3842, %-890, r16

