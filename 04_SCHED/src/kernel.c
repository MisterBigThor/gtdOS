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

#include "mode.h"

void process(char *array){
	while(1){
		for(int i = 0; i<5; ++i)
		printf("%c", array[i]);
		delay(90000);
	}
}
int version= 50;

void kernel_main(void){
	
	uart_init();
	printf("[GreenTreeOS] UART Comunication [UP]\r\n");
	printf("[GreenTreeOS] Version %u\r\n", version);
	printf("[GreenTreeOS] Exception level: %d Expect 1\r\n", get_el());
	
	irq_vector_init();

	init_scheduling();

	init_task( process,  "<<>>");
	init_task( process,  "****");
	init_task( process,  "++++");

	#if DBG
	generic_timer_init();
	#else
	timer_init();
	printf("[GreenTreeOS] Timer [UP]\r\n");
	#endif
	enable_interrupt_controller();
	enable_irq();
	printf("[GreenTreeOS] Timer interrupts [UP]\r\n");	
	
	uart_send_string_nl("[GreenTreeOS]Entering the main loop");
	
}
