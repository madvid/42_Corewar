.name		"all opcode"
.comment	"Test of all the combinaison of opcode et aguments"

ld		7, r2
ld		1042, r3
ld		%-42, r4
st		r1, r5
st		r3, -100
add		r1, r2, r6
sub		r1, r2, r7
or		r1, r2, r8
or		%-1, r3, r9
or		%0, r2, r10
or		4, r2, r11
or		7, -4, r12
or		%3, %1, r13
or		%3, 1, r14
xor		r1, r2, r8
xor		%-1, r3, r9
xor		%0, r2, r10
xor		4, r2, r11
xor		7, -4, r12
xor		%3, %1, r13
xor		%3, 1, r14
and		r1, r2, r8
and		%-1, r3, r9
and		%0, r2, r10
and		4, r2, r11
and		7, -4, r12
and		%3, %1, r13
and		%3, 1, r14
ldi		r1, r2, r15
ldi		-1025, %604, r16
ldi		-1025, r3, r2
sti		r3, %4096, %655
sti		r4, r6, r7
sti		r5, %-60, 100
lld		%780, r7
lld		4200, r7
lldi	r10, r15, r16
lldi	%675, 21, r11
lldi	3842, -890, r16


