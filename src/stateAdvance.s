.file	"stateAdvance.c"
	.p2align 
	.text
	
jt:
	.word default
	.word case1
	.word case2
	.word case3
	.word exit
	
isBlack:	.word 0

	.extern draw_square
	.extern state
	.global stateAdvance
	.text

stateAdvance:
	sub #4, r1
	mov #120, 0(r1)
	sub #30, 0(r1)
	mov r12, 2(r1)
	cmp.b #3, r12
	jnc default
	add r12, r12
	mov jt(r12), r0

default:		mov #0, r12
			mov #0, &isBlack
			add #4, r0
			pop r0
			

case1:			mov 0(r1), r12
			mov #15, r13
			call #draw_square
			add #1, 2(r1)
			mov 2(r1), r12
			jmp exit

case2:			mov 0(r1), r12
			mov #60, r13
			call #draw_square
			add #1, 2(r1)
			mov 2(r1), r12
			jmp exit

case3:			mov 0(r1), r12
			mov #105, r13
			call #draw_square
			add #1, 2(r1)
			mov 2(r1), r12
			jmp exit

exit:
			mov.b #0, r12
			add #4, r0
			pop r0
