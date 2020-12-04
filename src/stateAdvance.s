	.arch msp430g2553
	.p2align 
	
	.data
	
	.extern state
	
isBlack:	.word 0
	
	.text
jt:
	.word case0
	.word case1
	.word case2
	.word default
	.word exit
	
	.extern draw_square

	
	.global stateAdvance
	

stateAdvance:
	sub #4, r1
	mov #130, 0(r1)
	mov &state, r12
	mov r12, 2(r1)
	cmp.b #3, r12
	jhs default
	add r12, r12
	mov jt(r12), r0

default:		mov #0, &state
			mov #0, &isBlack
			add #4, r1
			pop r0
			

case0:			mov 0(r1), r12
			mov #15, r13
			call #draw_square
			add #1, &state
			jmp exit

case1:			mov 0(r1), r12
			mov #60, r13
			call #draw_square
			add #1, &state
			jmp exit

case2:			mov 0(r1), r12
			mov #105, r13
			call #draw_square
			add #1, &state
			jmp exit

exit:
			add #4, r1
			pop r0
