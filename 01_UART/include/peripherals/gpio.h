#ifndef	_P_GPIO_H
#define	_P_GPIO_H

#include "peripherals/base.h"

//going to use GPIO 17 FOR DEBUGIN
//FSEL17 = 1 for output mode
//SET0{17} FOR SETTING THE PIN
//CLR0{17} FOR UNSETTING THE PIN

//FUNCTION SELECTION REGISTERS
#define GPFSEL0         (PBASE+0x00200000)
#define GPFSEL1         (PBASE+0x00200004)
#define GPFSEL2         (PBASE+0x00200008)
#define GPFSEL3         (PBASE+0x0020000C)
#define GPFSEL4         (PBASE+0x00200010)
#define GPFSEL5         (PBASE+0x00200014)
//SET GPIO PIN n 
#define GPSET0          (PBASE+0x0020001C)
#define GPSET1          (PBASE+0x00200020)
//CLEAR GPIO PIN n
#define GPCLR0          (PBASE+0x00200028)
#define GPCLR1          (PBASE+0x0020002C)
//LEVEL OF THE REGISTER
#define GPLEV0          (PBASE+0x00200034)
#define GPLEV1          (PBASE+0x00200038)

//ACTUATION OF THE INTERNAL PULL-UP/DOWN CONTROL
#define GPPUD           (PBASE+0x00200094)

#define GPPUDCLK0       (PBASE+0x00200098)

#endif
