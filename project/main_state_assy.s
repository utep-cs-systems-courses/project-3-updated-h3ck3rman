	.arch msp430g2553
	.p2align 2
	.text

jt:
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
	mov #0, 0(r1)
	cmp.b #5, &button_state
	jhs exit
	mov.b &button_state, r12
	add.b r12, r12
	mov jt(r12), r0

case1:
	call #siren
	mov.b r12, 0(r1)
	jmp exit
case2:
	call #siren2
	mov.b r12, 0(r1)
	jmp exit
case3:
	call #diamond_font
	mov.b r12, 0(r1)
	jmp exit
case4:
	call #turn_off
	mov.b r12, 0(r1)
	jmp exit
exit:
	mov.b 0(r1), &led_changed
	add #2, r1
	call #led_update
	pop r0
 	
