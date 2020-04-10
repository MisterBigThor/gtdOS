#include "uart.h"
#include "utils.h"
#include "printf.h"
#include "gpio.h"

static unsigned int cur_proc = 0;

void haltUntilWork(void (* fn_ptr)(void *), void* data){
	
	while(1){
		if(fn_ptr != (void *)0) fn_ptr(data);
	}
}

void * workerP1 = (void *)0;
void * dataP1 = (void *)0;
void * workerP2 = (void *)0;
void * dataP2 = (void *)0;
void * workerP3 = (void *)0;
void * dataP3 = (void *)0;


void kernel_main(void){
  	unsigned long mpid = getmpid();
	if(mpid==0){
		uart_init();
		init_printf(0, putc);
	}
	while(cur_proc != mpid);
	printf("[GreenTreeOS] Processor %d \r\n", mpid);
	++cur_proc;
	if(mpid==1) haltUntilWork(workerP1, dataP1);
	if(mpid==2) haltUntilWork(workerP2, dataP2);
	if(mpid==3) haltUntilWork(workerP3, dataP3);

	while(cur_proc != 4); //CORE0: wait for all the cores to perform
	
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
