#ifndef	_inter_H
#define	_inter_H

/*
BCM 2835 MANUAL REFERENCE (pg 109)

*/

void enable_interrupt_controller(void);

void irq_vector_init(void);

void enable_irq(void);

void disable_irq(void);

#endif