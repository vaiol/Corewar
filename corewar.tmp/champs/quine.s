.name "quine"
.comment "dr_quine ;)"

start:	st		r1,13
		ld		%4,r7

live:	live	%1
		ld		%0,r3

while:	ldi		%:live,r3,r9
		sub		r9,r5,r6
		zjmp	%412
		add		r3,r7,r3
		sti		r9,%400,r3
		add		r8,r8,r8
		zjmp	%:while