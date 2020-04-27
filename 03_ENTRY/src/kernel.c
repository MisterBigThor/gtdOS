#include "uart.h"
#include "utils.h"
#include "printf.h"
#include "gpio.h"
#include "interrupt.h"
#include "timer.h"

#include "string.h"
#include "kernel.h"

int viewClock;

void parseOperation(string c){
	if(cmp(c, "clk")){
		if(viewClock) viewClock = 0;
		else viewClock = 1;
		printf("debugging clocks interrupts\r\n");
	}
	else if(cmp(c, "gpio")){
		printf("GPIO\r\n");
	}
	return;
}

void kernel_main(void){
	uart_init();
	viewClock = 0;
	init_printf(0, putc);
	printf("[GreenTreeOS] Hello, world with prinft\r\n");
	printf("[GreenTreeOS] Exception level: %d Expect 1\r\n", get_el());
	setfunctionGPIO(17, OUTPUT);
	
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();
	printf("[GreenTreeOS] Timer interrupts [UP]\r\n");	
	uart_send_string_nl("Entering the main loop\r\n");
	while (1) {
		string r = uart_read_string();
		uart_send_string("Recived via UART: ");
		uart_send_string_nl(r);
		parseOperation(r);		
	}
}
