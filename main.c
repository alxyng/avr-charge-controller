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
    float hysteresis = 1.0;
    int direction = 0; // 0 = hit float voltage - hysteresis most resently, 1 = hit float voltage most recently
    // how to init direction?
    int charging = 0;

	while (1) {
        voltage = map(adc_read(0), 0, 1023, 0.0, 19.67); // 100kohm, 33kohm 4.88 atmega vcc
        if (direction) { // 1
            if (voltage < float_voltage - hysteresis) {
                // Charge
                led_set_charging(1);
                led_set_charged(0);
                direction = 0;
                charging = 1;
            } else {
                // Do nothing
            }
        } else { // 0
            if (voltage > float_voltage) {
                // Stop charging
                led_set_charging(0);
                led_set_charged(1);
                direction = 1;
                charging = 0;
            } else {
                // Do nothing
            }
        }
        printf("voltage: %.2f ", voltage);
        printf(charging ? "(charging)\n" : "(discharging)\n");
        _delay_ms(100);
    }

    return 0;
}
