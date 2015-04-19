#include <stdio.h>

void uart_init();
unsigned char uart_getchar();
void uart_putchar(unsigned char c);
unsigned char uart_getchar_stream(FILE *stream);
int uart_putchar_stream(unsigned char c, FILE *stream);

FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar_stream, _FDEV_SETUP_READ);
FILE uart_output = FDEV_SETUP_STREAM(uart_putchar_stream, NULL, _FDEV_SETUP_WRITE);
