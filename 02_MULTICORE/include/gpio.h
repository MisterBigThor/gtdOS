/*
VICTOR CORREAL RAMOS
*/
#include "peripherals/gpio.h"
#include "utils.h"

#define INPUT   0
#define OUTPUT  1
#define FUNCT5  2
#define FUNCT4  3 
#define FUNCT3  7 
#define FUNCT2  6 
#define FUNCT1  5 
#define FUNCT0  4 

/*
Defines the functionality for a GPIO pin
*/
void setfunctionGPIO(int pin, const int F);

/*
If the pin functionality is OUTPUT, a '1' logic is set
*/
void setPin(int pin);

/*
If the pin functionality is OUTPUT, a '0' logic is set
*/
void clrPin(int pin);