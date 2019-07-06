.name "antizork"
.comment "F"

		sti r1, %:live, %1
		ld %0, r2
		fork %26 #create zork
live:	live %1 # 1 + 4
		zjmp %:live # 1 + 2
zork:
		sti r1, %:live1, %1
		ld %0, r2
live1:	live %1
		zjmp %:live1
