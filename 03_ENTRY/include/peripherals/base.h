#ifndef	_P_BASE_H
#define	_P_BASE_H

//BCM 2835 ARM peripherals 1.2.2:
//[...] thus a peripheral advertised here at bus @ 0x7Ennnnnn 
//is in physical @ 0x3Fnnnnnn
#define PBASE           0x3F000000
#define PEND            0x3FFFFFFF

#define LOCAL_PERIPHERALS_BASE 0x40000000


/*
VIRTUAL ADDRESSES:
0x00000000  USER INIT
0xBFFFFFFF 	USER END

0xC0000000	KERNEL INT
0xEFFFFFFF  KERNEL END

0xF2000000	PERIPHERALS INIT
0x			PERIPHERALS END
*/

#endif  /*_P_BASE_H */
