.name       "Test"
.comment    "Fuck this shit"
f:		ld 0, r2
		ld %0, r2
		st r2, r2
		st r2, 1
		lld %0, r6
entry:	sti r1, %:live, %1
live:	live %-1337
		add r1, r2, r3
		sub r1, r2, r3
		and r3, 0, r4
		and r3, %0, r4
		and r3, r2, r4
		or r3, 0, r4
		or r3, %0, r4
		or r3, r2, r4
		xor 0, r4, r3
		xor %0, r4, r3
		xor r2, r4, r3
		ld 0, r5
		zjmp %:kek
kek:	zjmp %:live
		ldi r2, %1337, r6
		ldi r1, r4, r5
		ldi %-1337, %1337, r5
		ldi r1, r5, r5
		sti r5, %1337, r5
		sti r5, 1337, %-1337
		live %-1
		fork %:entry
		lldi r2, %1337, r6
		lldi r1, r5, r5
		lldi %-1337, %1337, r5
		lldi r1, %0, r5
		lld 0, r6
		aff r6
		lfork %:entry
		ld 0, r6
		zjmp %:live
