#include "mm.h"

.section ".text.boot"

.globl _start
_start:
	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF
	cbz	x0, bss_init

	mov x0, #100
	bl delay
	b master
	
bss_init:
	adr x0, bss_begin
	adr x1, bss_end
	sub x1, x1, x0
	bl memzero
	b master

master:
	mrs x0, mpidr_el1
	and x0, x0, #0xFF
	mov x1, #LOW_MEMORY
	mov x2, #SECTION_SIZE
	mul x2, x2, x0
	add x1, x1, x2
	mov sp, x1

	bl kernel_main
	b proc_hang

proc_hang: 
	b 	proc_hang
