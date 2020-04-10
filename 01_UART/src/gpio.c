#include "gpio.h"

void setfunctionPin(int pin, const int F){
    unsigned int selector;
    if((pin >= 0) & (pin <=9)) selector = get32(GPFSEL0);
    else if((pin >= 10) & (pin <=19)) selector = get32(GPFSEL1);
    else if((pin >= 20) & (pin <=29)) selector = get32(GPFSEL2);
    else if((pin >= 30) & (pin <=39)) selector = get32(GPFSEL3);
    else if((pin >= 40) & (pin <=49)) selector = get32(GPFSEL4);
    else if((pin >= 50) & (pin <=53)) selector = get32(GPFSEL5);
    else return;
    int pinField = (pin%10)*3;
    selector &= ~(7<<pinField);                  //clean previous
    selector |= (F<<pinField);
}
void setPin(int pin){
    unsigned int selector;
    if((pin >= 0) & (pin <= 31)) selector = get32(GPSET0);
    else if((pin >= 32) & (pin <= 53)) selector = get32(GPSET1);
    else return;
    int pinField = pin%32;
    selector |= (1 << pinField);
}
void clrPin(int pin){
    unsigned int selector;
    if((pin >= 0) & (pin <= 31)) selector = get32(GPCLR0);
    else if((pin >= 32) & (pin <= 53)) selector = get32(GPCLR1);
    else return;
    int pinField = pin%32;
    selector |= (1 << pinField);
}
