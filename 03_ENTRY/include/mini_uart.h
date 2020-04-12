#ifndef	_MINI_UART_H
#define	_MINI_UART_H

//until dynamic memory, work with this:
#define BUFFERSIZE 256
char buff[BUFFERSIZE];

//n = (ClocFreq/(8*BAUDRATE)) -1;
#define BAUDRATE_9600	3254
#define BAUDRATE_19200	1626
#define BAUDRATE_38400	812
#define BAUDRATE_57600	541
#define BAUDRATE_115200	270

void mini_uart_init ( int baudrate );

char mini_uart_recv ( void );
char* mini_uart_read_string(void);

void mini_uart_send ( char c );
void mini_uart_send_string(char* str);
void mini_uart_send_string_nl(char *str);

void mini_putc(void* p, char c);
#endif  /*_MINI_UART_H */
