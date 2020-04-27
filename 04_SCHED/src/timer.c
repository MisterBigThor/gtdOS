#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "gpio.h"
#include "sched.h"

/*
	For setting a timer interval:
	The working frequency for the clock is 1MHz
	1 second -> 	interval 1*1MHz = 1.000.000 
	0.5 seconds ->  interval 500.000  
	the interval value range is 2^32 (the register size is 32 bits)
*/
const unsigned int interval = 500000;
unsigned int curVal = 0;
int l = 0;
extern int viewClock;
void timer_init ( void ){
	printf("[GreenTreeOS] Timer interval @%d\r\n", interval);
	curVal = get32(TIMER_CLO);
	curVal += interval;
	put32(TIMER_C1, curVal);
}

void handle_timer_irq( void ) {
	curVal += interval;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1);
	timer_tick();
}
