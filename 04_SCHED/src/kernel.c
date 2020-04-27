#include "uart.h"
#include "utils.h"
#include "printf.h"
#include "gpio.h"
#include "interrupt.h"
#include "timer.h"

#include "string.h"
#include "kernel.h"
#include "fork.h"
#include "sched.h"

void process(char *array){
	while(1){
		for(int i = 0; i<5; ++i)
		uart_send(array[i]);
		delay(100000);
	}
}

void kernel_main(void){
	
	uart_init();
	init_printf(0, putc);
	
	printf("[GreenTreeOS] Hello, world with prinft\r\n");
	printf("[GreenTreeOS] Exception level: %d Expect 1\r\n", get_el());
	
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();
	printf("[GreenTreeOS] Timer interrupts [UP]\r\n");	
	int res = copy_process((unsigned long)&process, (unsigned long)"12345");
    if (res != 0) {
        printf("error while starting process 1");
        return;
    }
    res = copy_process((unsigned long)&process, (unsigned long)"abcde");
    if (res != 0) {
        printf("error while starting process 2");
        return;
    }

    while (1){
        schedule();
    }
	
	uart_send_string_nl("[GreenTreeOS]Entering the main loop");
	while (1) {
		schedule();	
	}
}
