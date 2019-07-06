.name "antizork"
.comment "I'am Ricardo"

		sti r1, %:live, %1
		and r1, %0, r1
		fork %0
live:	live %1
		zjmp %:live
