#include "utils.h"
#include "printf.h"
#include "timer.h"
#include "arm/entry.h"
#include "peripherals/interrupt.h"
#include "interrupt.h"

#include "mode.h"

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};


void enable_interrupt_controller(){
	// Enables Core 0 Timers interrupt control for the generic timer 
	#if DBG
    put32(TIMER_INT_CTRL_0, TIMER_INT_CTRL_0_VALUE);
	#else
	put32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
	#endif
}

void show_invalid_entry_message(int type, unsigned long esr, unsigned long address){
	printf("\r\n\r\n%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
	switch(esr>>26) {
        case 0b000000: printf("Unknown"); break;
        case 0b000001: printf("Trapped WFI/WFE"); break;
        case 0b001110: printf("Illegal execution"); break;
        case 0b010101: printf("System call"); break;
        case 0b100000: printf("Instruction abort, lower EL"); break;
        case 0b100001: printf("Instruction abort, same EL"); break;
        case 0b100010: printf("Instruction alignment fault"); break;
        case 0b100100: printf("Data abort, lower EL"); break;
        case 0b100101: printf("Data abort, same EL"); break;
        case 0b100110: printf("Stack alignment fault"); break;
        case 0b101100: printf("Floating point"); break;
        default: printf("Unknown"); break;
    }
	 if(esr>>26==0b100100 || esr>>26==0b100101) {
        printf(", ");
        switch((esr>>2)&0x3) {
            case 0: printf("Address size fault"); break;
            case 1: printf("Translation fault"); break;
            case 2: printf("Access flag fault"); break;
            case 3: printf("Permission fault"); break;
        }
        switch(esr&0x3) {
            case 0: printf(" at level 0"); break;
            case 1: printf(" at level 1"); break;
            case 2: printf(" at level 2"); break;
            case 3: printf(" at level 3"); break;
        }
    }
	printf("\r\n");
}
#if DBG
void handle_irq(void){
	unsigned int irq = get32(INT_SOURCE_0);
	switch (irq) {
		case (GENERIC_TIMER_INTERRUPT):
			handle_generic_timer_irq();
			break;
		default:
			printf("Unknown pending irq: %x\r\n", irq);
	}
}
#else
void handle_irq(void){
	unsigned int irq = get32(IRQ_PENDING_1);
	switch (irq) {
		case (SYSTEM_TIMER_IRQ_1):
			handle_timer_irq();
			break;
		default:
			printf("Unknown pending irq: %x\r\n", irq);
	}
}
#endif
