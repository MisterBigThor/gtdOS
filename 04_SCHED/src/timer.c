#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "gpio.h"
#include "taskScheduling.h"
#include "timer.h"

/*
	For setting a timer interval:
	The working frequency for the clock is 1MHz
	1 second -> 	interval 1*1MHz = 1.000.000 
	0.5 seconds ->  interval 500.000  
	0.1 seconds ->	interval 100.000
	the interval value range is 2^32 (the register size is 32 bits)
*/
#define TIMER_PER_TICK 	0.5
const unsigned int interval = 500000;

unsigned int curVal = 0;
unsigned int sysTicks;
extern int viewClock;

void timer_init ( void ){
	printf("[GreenTreeOS] Timer interval @%d\r\n", interval);
	curVal = get32(TIMER_CLO);
	curVal += interval;
 	sysTicks = 0;
	put32(TIMER_C1, curVal);
}

void handle_timer_irq( void ) {
	curVal += interval;
	sysTicks++;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1);
	enable_irq();
	timerNotify();
	disable_irq();
}

int get_ticks(void){
	return curVal;
}
int get_time(void){
	return sysTicks;
}
void generic_timer_init ( void ){
	gen_timer_init();
	gen_timer_reset();
}

void handle_generic_timer_irq( void ) {
	gen_timer_reset();
	enable_irq();
	timerNotify();
	disable_irq();
}
