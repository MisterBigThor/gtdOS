#ifndef	_UART_H
#define	_UART_H

#define BUFFERSIZE 256
char buff[BUFFERSIZE];


void uart_init (void);
char uart_recv (void);
char* uart_read_string(void);

void uart_send (char c);
void uart_send_string(char* str);
void uart_send_string_nl(char *str);

void putc(void* p, char c);
#endif  /*_UART_H */
