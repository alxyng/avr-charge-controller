#include <avr/io.h>
#include <stdio.h>

#include "adc.h"
#include "led.h"
#include "uart.h"
#include "util.h"

#ifndef F_CPU
#   define F_CPU 4000000UL
#endif

#include <util/delay.h>

// possible to store voltage as two uint8_ts in the future for performance
//  and more space

#define V_FLT   13.9    // Battery float voltage (voltage when charged)
#define HYST    1.0     // Hysteresis (dv below float voltage before charging again)

#define ADC_MIN 0
#define ADC_MAX 1023
#define V_MIN   0.0
#define V_MAX   19.67

int main(void) {
    int charging = 1;   // Charging state, default 1 if v < V_FLT
    float v;            // Current battery voltage

    led_init();
    adc_init();
    uart_init();
    uart_enable_interrupts();

	while (1) {
        v = map(adc_read(0), ADC_MIN, ADC_MAX, V_MIN, V_MAX); // 100kohm, 33kohm 4.88 atmega vcc
        if (charging) {
            if (v > V_FLT) {
                // Discharge
                led_charging_off();
                led_charged_on();
                charging = 0;
            }
        } else {
            if (v <= V_FLT - HYST) {
                // Charge
                led_charging_on();
                led_charged_off();
                charging = 1;
            }
        }

        if (uart_char_available()) {
            unsigned char cmd;
            char buf[6];

            cmd = uart_getchar();
            switch (cmd) {
                case 'v':
                    voltage_to_str(buf, v);
                    printf("voltage: %s ", buf);
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
