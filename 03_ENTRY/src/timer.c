#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "gpio.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;
int l = 0;

void timer_init ( void ){
	printf("[GreenTreeOS] Timer init:\r\n");
	curVal = get32(TIMER_CLO);
	curVal += interval;
	put32(TIMER_C1, curVal);
}

void handle_timer_irq( void ) {
	curVal += interval;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1);
	printf("Timer interrupt received\n\r");
	if(l == 0){
		setPin(17);
		l = 1;
	}
	else {
		clrPin(17);
		l = 0;
	}
}
