#include <stdio.h>

#include "main.h"
#include "uart.h"

#define F_CPU 8000000UL // 8 MHz

#include <util/delay.h>

int main() {
    uart_init();
    //stdout = &uart_output;  // move to uart_init_stream?
    //stdin  = &uart_input;   // "

    //char c;

	while (1) {
        //printf("You wrote %d\n", 123);
        uart_putchar('A');
        _delay_ms(250);
        uart_putchar('L');
        _delay_ms(250);
        uart_putchar('E');
        _delay_ms(250);
        uart_putchar('X');
        _delay_ms(250);
    }

    return 0;
}
