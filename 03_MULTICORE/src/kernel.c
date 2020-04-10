#include "uart.h"
#include "utils.h"
#include "printf.h"
#include "gpio.h"

static unsigned int cur_proc = 0;

void kernel_main(void){
  	unsigned long mpid = getmpid();
	if(mpid==0) uart_init();
	while(cur_proc != mpid);

	uart_send_string("Hello, from processor ");
	uart_send(mpid + '0');
	uart_send_string("\r\n");

	++cur_proc;
	if(mpid!=0) while(1){}

	while(cur_proc != 4); //CORE0: wait for all the cores to perform
	init_printf(0, putc); //move to the uart init function!
	printf("[GreenTreeOS] Found %d cores, executing over Core0\r\n", cur_proc);
	printf("[GreenTreeOS] Hello, world w/ prinft\r\n");
	printf("[GreenTreeOS] Actual exception level: %d \r\n", get_el());
	setfunctionGPIO(17, OUTPUT);
	setPin(17);
	uart_send_string_nl("[GreenTreeOS] KERNEL MAIN: UART ECHO");
	while (1) {
		char *c = uart_read_string();
		uart_send_string("Recived via UART: ");
		uart_send_string_nl(c);
	}
}
