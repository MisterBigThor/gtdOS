#ifndef __timer_h
#define __timer_h

void timer_init (void);
void handle_timer_irq (void);

void generic_timer_init (void);
void handle_generic_timer_irq( void );

int get_ticks(void);

extern void gen_timer_init(void);
extern void gen_timer_reset(void);
#endif