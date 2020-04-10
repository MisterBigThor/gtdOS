#include "uart.h"
#include "utils.h"
#include "printf.h"
#include "gpio.h"

extern int get_el();
static unsigned int cur_proc = 0;

void kernel_main(void){

	uart_init();
	init_printf(0, putc); //move to the uart init function!
	printf("[GreenTreeOS] Hello, world with prinft\r\n");
	uart_send_string_nl("[GreenTreeOS] Hello, world!");
	printf("[GreenTreeOS] Exception level: %d \r\n", get_el());
	setfunctionGPIO(17, OUTPUT);
	uart_send_string_nl("KERNEL MAIN: UART ECHO");
	setPin(17);
	while (1) {
		char *c = uart_read_string();
		uart_send_string("Recived via UART: ");
		uart_send_string_nl(c);
	}
}
