	.text
	.global isNegative

isNegative:
	cmp #0, r12
	jn negative
	
notNegative:
	mov #0, r12
	pop r0

negative:
	mov #1, r12
	pop r0
