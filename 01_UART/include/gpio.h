/*
VICTOR CORREAL RAMOS
*/
#include "peripherals/gpio.h"
#include "utils.h"

#define OUTPUT  0
#define INPUT   1
#define FUNCT5  2
#define FUNCT4  3 
#define FUNCT3  7 
#define FUNCT2  6 
#define FUNCT1  5
#define FUNCT0  4

/*
*/
void setfunctionPin(int pin, const int F);

/*
*/
void setPin(int pin);

/*
*/
void clrPin(int pin);