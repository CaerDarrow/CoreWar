.name       "Batman"
.comment    "This city needs me"
	sti r1, %:live, %1 
	xor %1, %1, r16
live:
	sti	r2, %5, %-5
	live %0
	fork %:live
	zjmp %:live
