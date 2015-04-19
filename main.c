#include <avr/io.h>
#include <stdio.h>

#include "adc.h"
#include "led.h"
#include "uart.h"

#define F_CPU 8000000UL // 8 MHz

#include <util/delay.h>

// possible to store voltage as two uint8_ts in the future for performance and more space(no float to string conversion)

float map(unsigned int input, unsigned int in_min, unsigned int in_max, float out_min, float out_max) {
    return (((out_max - out_min) / (in_max - in_min)) * input) + in_min;
}

int main() {
    led_init();
    adc_init();

    uart_init();
    stdout = &uart_output;  // move to uart_init_stream?
    stdin  = &uart_input;   // "

    float voltage;
    float float_voltage = 13.9;

    unsigned int temp;

	while (1) {
        voltage = map(adc_read(0), 0, 1023, 0.0, 20.0);
        if (voltage < float_voltage) {
            led_set_charging(1);
            led_set_charged(0);
            printf("voltage: %.2f (charging)\n", voltage);
        } else {
            led_set_charging(0);
            led_set_charged(1);
            printf("voltage: %.2f (charged)\n", voltage);
        }
        //printf("voltage: %.2f\n", voltage);
        // seems that when i enable another printf statement, it prints the right value for voltage...wierd...
        //printf("ADCH: %u, ADHL: %u, ADC: %u\n", ADCH, ADCL, ADC);
        //printf("");
        temp = ADC;
        _delay_ms(100);
    }

    return 0;
}
