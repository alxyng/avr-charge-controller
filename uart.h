#ifndef UART_H_
#define UART_H_

#include <stdio.h>

#ifndef F_CPU
#	define F_CPU 4000000UL
#endif

#ifndef BAUD
#	define BAUD 38400
#endif

#include <util/setbaud.h>

void uart_init(void);
void uart_enable_interrupts(void);
void uart_disable_interrupts(void);
unsigned char uart_char_available(void);
unsigned char uart_getchar(void);
void uart_putchar(unsigned char c);
unsigned char uart_getchar_stream(FILE *stream);
void uart_putchar_stream(unsigned char c, FILE *stream);
void uart_handle_rxc_isr(void);

#endif /* UART_H_ */
