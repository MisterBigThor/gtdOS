#include "utils.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"
#include "uart.h"
#include "gpio.h"

void uart_init (void){

	setfunctionGPIO(14, FUNCT0);
	setfunctionGPIO(15, FUNCT0);
	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

	put32(UART_CR,0);	// disable RX and TX to configure
	
	put32(UART_IBRD,26);	//PrimeCell UART (PL011) rev.r1p5 pag.3-9 BAUDDIV = (FUARTCLK/(16 Baud rate)) = 48MHz/(16*115200) = 26.041666
	put32(UART_FBRD,3);					
	put32(UARTLCR_LCRH,0x60);	//Enable 8 bit mode

	put32(UART_CR,0x301);		// enable UART, RX and TX
}



void uart_send ( char c ){
	while(get32(UART_FR)&0x20) {}			// wait if TX is full
	put32(UART_DR,c);						// when TX is empty, send next char
}

char uart_recv ( void ){
	while(get32(UART_FR)&0x10) {}			// wait if RX is empty
	return(get32(UART_DR)&0xFF);			// get recived char
}

void uart_send_string(char* str){
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}
void uart_send_string_nl(char *str){
	uart_send_string(str);
	uart_send_string("\r\n");
}
//Add:
char* uart_read_string(void){
	int n = 0;
	while(n < BUFFERSIZE-1){
		char c = uart_recv();
		if((c != '\r') & (c != '\n')) {
			buff[n++] = c;
			uart_send(c);
		}
		else {
			buff[n++] = '\0';
			uart_send_string("\r\n");
			return buff;
		}
	}
	buff[n++] = '\0';
	uart_send_string("\r\n");
	return buff;
}
void putc(void* p, char c){
	uart_send(c);
}