	.text
	.global is_positive

is_positive:
	cmp #0, r12
	jge positive

negative:
	mov #0, r12
	pop r0

positive:
	mov #1, r12
	pop r0
