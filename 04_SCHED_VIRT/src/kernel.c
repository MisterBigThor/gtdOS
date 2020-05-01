#include "uart.h"
#include "utils.h"
#include "printf.h"
#include "gpio.h"
#include "interrupt.h"
#include "timer.h"

#include "string.h"
#include "kernel.h"
#include "fork.h"
#include "taskScheduling.h"

void process(char *array){
	while(1){
		for(int i = 0; i<5; ++i)
		uart_send(array[i]);
		delay(5000000);
	}
}

void kernel_main(void){
	
	uart_init();
	init_printf(0, putc);
	
	printf("[GreenTreeOS] Hello, world with prinft\r\n");
	printf("[GreenTreeOS] Exception level: %d Expect 1\r\n", get_el());
	
	irq_vector_init();

	init_scheduling();

	init_tasks((unsigned long) process, (unsigned long) "abcd");
	init_tasks((unsigned long) process, (unsigned long) "****");
	init_tasks((unsigned long) process, (unsigned long) "kkkkk");

	generic_timer_init();
	enable_interrupt_controller();
	enable_irq();
	printf("[GreenTreeOS] Timer interrupts [UP]\r\n");	
	
	
	uart_send_string_nl("[GreenTreeOS]Entering the main loop");
	while (1) {
		//
	}
}
