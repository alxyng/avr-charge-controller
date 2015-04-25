#include <avr/io.h>
#include <stdio.h>

#include "adc.h"
#include "led.h"
#include "uart.h"
#include "util.h"

#ifndef F_CPU
#define F_CPU 4000000UL
#endif

#include <util/delay.h>

// possible to store voltage as two uint8_ts in the future for performance and more space (no float to string conversion)

int main() {
    led_init();
    adc_init();

    uart_init();
    uart_enable_interrupts();

    float voltage;
    float float_voltage = 13.9;
    float hysteresis = 1.0;
    int charging = 1; // Charging by default if voltage is less than float_voltage

	while (1) {
        voltage = map(adc_read(0), 0, 1023, 0.0, 19.67); // 100kohm, 33kohm 4.88 atmega vcc
        if (charging) {
            if (voltage > float_voltage) {
                // Discharge
                led_charging_set(0);
                led_charged_set(1);
                charging = 0;
            }
        } else {
            if (voltage < float_voltage - hysteresis) {
                // Charge
                led_charging_set(1);
                led_charged_set(0);
                charging = 1;
            }
        }

        if (uart_char_available()) {
            unsigned char cmd = uart_getchar();
            switch (cmd) {
                case 'v':
                    printf("voltage: %.2f ", voltage);
                    printf(charging ? "(charging)\n" : "(discharging)\n");
                    break;
            }
        }
    }

    return 0;
}

/* Interrupt service routines */

ISR(USART_RXC_vect) {
    uart_handle_rxc_isr();
}
