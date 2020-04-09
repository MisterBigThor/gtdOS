#ifndef	_MINI_UART_H
#define	_MINI_UART_H
/*
MINI UART HEADER
*/
//until dynamic memory, work with this:
#define BUFFERSIZE 256
char buff[BUFFERSIZE];

void uart_init ( void );

char uart_recv ( void );
char* uart_read_string(void);

void uart_send ( char c );
void uart_send_string(char* str);
void uart_send_string_nl(char *str);

#endif  /*_MINI_UART_H */
