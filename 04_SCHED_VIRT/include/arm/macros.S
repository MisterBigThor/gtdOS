
.macro handle_invalid_entry type
	SAVE_REGISTERS
	mov	x0, #\type
	mrs	x1, esr_el1
	mrs	x2, elr_el1
	bl	show_invalid_entry_message
	b	err_hang
.endm

.macro	ventry	label
	.align	7
	b	\label
.endm
