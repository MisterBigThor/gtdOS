#include "mini_uart.h"

void kernel_main(void)
{
	uart_init();
	uart_send_string_nl("[GreenTreeOS]Hello, world!");
	uart_send_string_nl("KERNEL MAIN: UART ECHO");
	while (1) {
//		char *c = uart_read_string();
//		uart_send_string("Recived via UART: ");
//		uart_send_string_nl(c);
		uart_send(uart_recv());
	}
}
