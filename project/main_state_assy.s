	.arch msp430g2553
	.p2align 2
	.text

jt:				;constant in flash memory
	.word exit
	.word case1
	.word case2
	.word case3
	.word case4

	.extern button_state
	.extern led_changed

	.global main_state
main_state:			
	sub #2, r1
	mov #0, 0(r1)		;led_changed in 0(r1) = 0
	cmp.b #5, &button_state	;compare 5 with the button state
	jhs exit		;if button_state >= 5, then goto exit
	mov.b &button_state, r12
	add.b r12, r12		;button_state*2
	mov jt(r12), r0		;goto jt[button_state]

case1:
	call #draw_states
	mov.b r12, 0(r1)	;led_changed value = draw_states
	jmp exit		;goto exit
case2:
	call #siren
	mov.b r12, 0(r1)	;led_changed value = siren
	jmp exit		;goto exit
case3:
	call #siren2
	mov.b r12, 0(r1)	;led_changed value = siren2
	jmp exit		;goto exit
case4:
	call #turn_off
	mov.b r12, 0(r1)	;led_changed value = turn_off
	jmp exit		;goto exit
exit:
	mov.b 0(r1), &led_changed ;0(r1) moved to led_changed address
	add #2, r1		  ;move stack pointer
	call #led_update
	pop r0			;return to caller
 	
