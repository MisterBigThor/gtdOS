#include "utils.h"
#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"
#include "mini_uart.h"

void mini_uart_send_string(char *str);

void mini_uart_send ( char c )
{
	while(1) {
		if(get32(AUX_MU_LSR_REG)&0x20) 
			break;
	}
	put32(AUX_MU_IO_REG,c);
}

char mini_uart_recv ( void )
{
	while(1) {
		if(get32(AUX_MU_LSR_REG)&0x01) 
			break;
	}
	return(get32(AUX_MU_IO_REG)&0xFF);
}

/**
 * A string ends with \r or \n
 */

char* mini_uart_read_string(void){
	int n = 0;
	while(n < BUFFERSIZE-1){
		char c = mini_uart_recv();
		if((c != '\r') & (c != '\n')) {
			buff[n++] = c;
			mini_uart_send(c);
		}
		else {
			buff[n++] = '\0';
			mini_uart_send_string("\r\n");
			return buff;
		}
	}
	buff[n++] = '\0';
	mini_uart_send_string("\r\n");
	return buff;
}

void mini_uart_send_string(char* str){
	for (int i = 0; str[i] != '\0'; i ++) {
		mini_uart_send((char)str[i]);
	}
}
void mini_uart_send_string_nl(char *str){
	mini_uart_send_string(str);
	mini_uart_send_string("\r\n");
}

void mini_uart_init ( int baudrate ){
	unsigned int selector;

	if(baudrate == 0) baudrate = BAUDRATE_115200;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 2<<12;                      // set alt5 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 2<<15;                      // set alt5 for gpio15
	put32(GPFSEL1,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

	put32(AUX_ENABLES,1);                   //Enable mini uart (this also enables access to it registers)
	put32(AUX_MU_CNTL_REG,0);               //Disable auto flow control and disable receiver and transmitter (for now)
	put32(AUX_MU_IER_REG,0);                //Disable receive and transmit interrupts
	put32(AUX_MU_LCR_REG,3);                //Enable 8 bit mode
	put32(AUX_MU_MCR_REG,0);                //Set RTS line to be always high
	put32(AUX_MU_BAUD_REG,baudrate);        //Set baud rate to 115200

	put32(AUX_MU_CNTL_REG,3);               //Finally, enable transmitter and receiver
	mini_uart_send_string("[UART]: Done init UART @ 115200\r\n");
}

void mini_putc(void* p, char c){
	mini_uart_send(c);
}