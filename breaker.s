.name "breaker"
.comment "breaks on wait"

start:
	ld	0,r7
	st	r7,13
	and	r1,r1,r1
	zjmp	%:start
