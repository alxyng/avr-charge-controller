#include <stdio.h>

#include "adc.h"
#include "uart.h"

#define F_CPU 8000000UL // 8 MHz

#include <util/delay.h>

int main() {
    adc_init();

    uart_init();
    stdout = &uart_output;  // move to uart_init_stream?
    stdin  = &uart_input;   // "

    char c;
    unsigned char voltage;

	while (1) {
        /*
        printf("What would you like to read?\n");
        c = getchar();
        if (c == 'V' || c == 'v') {
            fprintf(stdout, "Current voltage: %.2f\n", voltage);
        } else {
            printf("Invalid input\n");
        }
        */
        voltage = adc_read();
        //printf("Voltage: %.2f\n", voltage);
        printf("Voltage: %d\n", voltage);
        _delay_ms(250);

        //c = uart_getchar();
        //uart_putchar(c);
    }

    return 0;
}
