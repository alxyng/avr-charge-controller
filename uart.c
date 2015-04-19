#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

#define F_CPU 8000000UL
#define BAUD 300

#include <util/setbaud.h>

void uart_init() {
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

    #if USE_2X
        UCSRA |= (1 << U2X);
    #else
        UCSRA &= ~(1 << U2X);
    #endif

    UCSRC = (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data
    UCSRB = (1 << RXEN) | (1 << TXEN);   // Enable RX and TX
}

char uart_getchar() {
    while (!(UCSRA & (1 << RXC))) {}    // Wait until RXC bit is set in UCSRA
    return UDR;
}

void uart_putchar(uint8_t c) {
    while (!(UCSRA & (1 << UDRE))) {}   // Wait until UDRE bit is set in UCSRA
    UDR = c;
}

char uart_getchar_stream(FILE *stream) {
    return uart_getchar();
}

int uart_putchar_stream(uint8_t c, FILE *stream) {
    if (c == '\n') {
        uart_putchar_stream('\r', stream);
    }
    uart_putchar(c);

    return 0;
}
