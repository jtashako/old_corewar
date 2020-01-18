.name "ld test"
.comment "ld test acb > 2 args"

start:
	ld %:point,r7
	ld %0,r2
	ld %1,r3
loop:	
	st r7, :point
	add r7,r2,r7
	#ld %42,r8
	ldi %4095, %42, r65 
	ldi %4095, %42, r65 
	and r3, r3, r3
	and r2, r2, r2
	and r2, r2, r2
	#ld %655117, r8
	ld %655092, r8
	st r8, 200
	zjmp %:loop
	live	%0
	live	%0
	and r2, r2, r2
point:	
