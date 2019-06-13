.name       "Batman"
.comment    "This city needs me"
	sti r1, %:live, %1
kek:
	ld %0, r2
live:
	live %0
	fork %:live
	zjmp %:kek
