.name "fuck"
.comment "shit"

start:
	ld %:point,r7
	ld %1,r2
loop:	
	st r7,:point
	add r7,r2,r7
	#ld %42,r8
	ldi %4095, %42, r65 
	ldi %4095, %42, r65 
	add r3,r3,r3
	add r3,r3,r3
	add r3,r3,r3
	zjmp %:loop
	live	%0
	live	%0
point:	
