.name		"Testssssssssssssss"
.comment	"Test Bot"


#live %-1
#l2:   sti r1,%:live,%1
#      and r2,%0,r2
#live: live %1
#      zjmp %:live

#ld %:init, r10
#add r10, r10, r5
#ld %-182, r5
#init:		ld   %100,r6		 	#7
#		ld   %04,r12		#7
#		zjmp %-200

#sti r5, 15, %100
#sti r12, %:init, %104
aff r1
aff r1
#lfork %5000

#ld %10, r96

#sti r96, %3840, r15

#ld %10, r5
#lldi 3, %0, r2

#sti r2, 2, %-3
