#ifndef __timer_h
#define __timer_h

void timer_init (void);
void handle_timer_irq (void);
int get_ticks(void);

#endif