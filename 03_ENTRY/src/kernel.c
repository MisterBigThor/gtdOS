#include "uart.h"
#include "utils.h"
#include "printf.h"
#include "gpio.h"
#include "interrupt.h"
#include "timer.h"


void kernel_main(void){
	uart_init();
	init_printf(0, putc);
	printf("[GreenTreeOS] Hello, world with prinft\r\n");
	printf("[GreenTreeOS] Exception level: %d Expect 1\r\n", get_el());
	setfunctionGPIO(17, OUTPUT);
	setPin(17);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();
	printf("[GreenTreeOS] Timer interrupts [UP]");	
	uart_send_string_nl("KERNEL MAIN: UART ECHO");
	while (1) {
		char *c = uart_read_string();
		uart_send_string("Recived via UART: ");
		uart_send_string_nl(c);
	}
}
