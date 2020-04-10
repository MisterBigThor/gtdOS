#include "uart.h"
#include "utils.h"
#include "printf.h"

void kernel_main(void)
{
	uart_init();
	init_printf(0, putc); //move to the uart init function!
	uart_send_string_nl("[GreenTreeOS] Hello, world!");
	printf("[GreenTreeOS] Exception level: %d \r\n", get_el());
	uart_send_string_nl("KERNEL MAIN: UART ECHO");
	while (1) {
//		char *c = uart_read_string();
//		uart_send_string("Recived via UART: ");
//		uart_send_string_nl(c);
		uart_send(uart_recv());
		uart_send_string("\r\n");
	}
}
