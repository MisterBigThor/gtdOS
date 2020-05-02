#include "gpio.h"

void setfunctionGPIO(int pin, const int F){
    unsigned int value;
    int r;
    if((pin >= 0) & (pin <=9))        {
        value = get32(GPFSEL0);
        r = GPFSEL0; 
    }
    else if((pin >= 10) & (pin <=19)) {
        value = get32(GPFSEL1);
        r = GPFSEL1; 
    }
    else if((pin >= 20) & (pin <=29)) {
        value = get32(GPFSEL2);
        r = GPFSEL2; 
    }
    else if((pin >= 30) & (pin <=39)) {
        value = get32(GPFSEL3);
        r = GPFSEL3; 
    }
    else if((pin >= 40) & (pin <=49)) {
        value = get32(GPFSEL4);
        r = GPFSEL4; 
    }
    else if((pin >= 50) & (pin <=53)) {
        value = get32(GPFSEL5);
        r = GPFSEL5; 
    }
    else return;
    int pinField = (pin%10)*3;
    value &= ~(7<<pinField);                  //clean previous
    value |= (F<<pinField);
    put32(r, value);
}
void setPin(int pin){
    unsigned int value;
    int r;
    if((pin >= 0) & (pin <= 31)) {
        value = get32(GPSET0);
        r = GPSET0;
    }
    else if((pin >= 32) & (pin <= 53)){
        value = get32(GPSET1);
        r = GPSET1;
    }
    else return;
    int pinField = pin%32;
    value |= (1 << pinField);
    put32(r, value);
}
void clrPin(int pin){
    unsigned int value;
    int r;
    if((pin >= 0) & (pin <= 31)) {
        value = get32(GPCLR0);
        r = GPCLR0;
    }
    else if((pin >= 32) & (pin <= 53)){
        value = get32(GPCLR1);
        r = GPCLR1;
    }
    else return;
    int pinField = pin%32;
    value |= (1 << pinField);
    put32(r, value);
}
level levelPin(int pin){
    unsigned int value;
    if((pin >= 0) & (pin <= 31)) {
        value = get32(GPLEV0);
    }
    else if((pin >= 32) & (pin <= 53)) {
        value = get32(GPLEV1);
    }
    int pinField = pin%32;
    value = value<<pinField;
    if(value) return LVL_HIGH;
    else return LVL_LOW;
}