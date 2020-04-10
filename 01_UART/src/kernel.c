#include "uart.h"
#include "utils.h"
#include "printf.h"
#include "gpio.h"

extern int get_el();
static unsigned int cur_proc = 0;

void kernel_main(void){
	unsigned long procID = getmpid();
	if(procID == 0) uart_init();
	while(cur_proc != procID);

	uart_send_string("Hello, from processor ");
	uart_send(procID + '0');
  	uart_send_string("\r\n");

  	++cur_proc;

	if(procID != 0) while(1){}

	init_printf(0, putc); //move to the uart init function!
	uart_send_string_nl("[GreenTreeOS] Hello, world!");
	printf("[GreenTreeOS] Exception level: %d \r\n", get_el());
	setfunctionGPIO(17, OUTPUT);
	uart_send_string_nl("KERNEL MAIN: UART ECHO");
	while (1) {
		char *c = uart_read_string();
		uart_send_string("Recived via UART: ");
		uart_send_string_nl(c);
	}
}
