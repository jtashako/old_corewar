.name "cycle to die liver"
.comment "emits live call on 1536"

start:	lfork %0		#1000
	lldi  r0, r0, r0	#50
	lldi  r0, r0, r0	#50
	lldi  r0, r0, r0	#50
	lldi  r0, r0, r0	#50
	lldi  r0, r0, r0	#50
	lldi  r0, r0, r0	#50
	lldi  r0, r0, r0	#50
	lldi  r0, r0, r0	#50
	lldi  r0, r0, r0	#50
	lldi  r0, r0, r0	#50
	add   r1, r1, r1	#10
	add   r1, r1, r1	#10
	and   r0, r0, r0	#6
	live	%-1
