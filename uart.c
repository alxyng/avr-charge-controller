#include <avr/io.h>
#include <stdio.h>

#define F_CPU 8000000UL
#define BAUD 9600
#define UBRR_VAL (F_CPU / (16UL * BAUD)) - 1

void uart_init() {
    UBRRH = (UBRR_VAL >> 8);
    UBRRL = UBRR_VAL;

    /*
    #if USE_2X
        UCSRA |= (1 << U2X);
    #else
        UCSRA &= ~(1 << U2X);
    #endif
    */

    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data
    UCSRB = (1 << RXEN) | (1 << TXEN);   // Enable RX and TX
}

unsigned char uart_getchar() {
    while (!(UCSRA & (1 << RXC))) {}    // Wait until RXC bit is set in UCSRA
    return UDR;
}

void uart_putchar(unsigned char c) {
    while (!(UCSRA & (1 << UDRE))) {}   // Wait until UDRE bit is set in UCSRA
    UDR = c;
}

unsigned char uart_getchar_stream(FILE *stream) {
    return uart_getchar();
}

void uart_putchar_stream(unsigned char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar_stream('\r', stream);
    }
    uart_putchar(c);
}
