#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "uart.h"

FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar_stream, _FDEV_SETUP_READ);
FILE uart_output = FDEV_SETUP_STREAM(uart_putchar_stream, NULL, _FDEV_SETUP_WRITE);

static unsigned char available;
static unsigned char uart_interrupt_char;

void uart_init(void) {
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

#if USE_2X
    UCSRA |= (1 << U2X);
#else
    UCSRA &= ~(1 << U2X);
#endif

    // When first trying to use 9600 baud, URSEL bit wasnt set and the baud was 300
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data
    UCSRB = (1 << RXEN) | (1 << TXEN);   // Enable RX and TX

    stdout = &uart_output;  // move to uart_init_stream?
    stdin  = &uart_input;   // "
}

void uart_enable_interrupts(void) {
    sei(); // Enable global interrupts
    UCSRB |= (1 << RXCIE);
}

void uart_disable_interrupts(void) {
    cli(); // Disable global interrupts
    UCSRB &= ~(1 << RXCIE);
}

unsigned char uart_char_available(void) {
    return available;
}

unsigned char uart_getchar(void) {
    if (UCSRB & (1 << RXCIE)) {
        available = 0;
        return uart_interrupt_char;
    }

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

ISR(USART_RXC_vect) {
    available = 1;
    uart_interrupt_char = UDR;
}
