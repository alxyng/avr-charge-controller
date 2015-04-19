#include <stdio.h>

#include "uart.h"

#define F_CPU 8000000UL // 8 MHz

#include <util/delay.h>

int main() {
    uart_init();
    stdout = &uart_output;  // move to uart_init_stream?
    stdin  = &uart_input;   // "

    char c;
    float voltage = 1.23;

	while (1) {
        printf("What would you like to read?\n");
        c = getchar();
        if (c == 'V' || c == 'v') {
            fprintf(stdout, "Current voltage: %.2f\n", voltage);
        } else {
            printf("Invalid input\n");
        }

        //c = uart_getchar();
        //uart_putchar(c);
    }

    return 0;
}
