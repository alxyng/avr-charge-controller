#include <avr/io.h>
#include <stdio.h>

#include "adc.h"
#include "led.h"
#include "mosfet.h"
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
#define V_MAX   19.67   // 100kohm, 33kohm ATmega8 vcc 4.88

static unsigned char charging; // Charging state

static void charger_start() {
    mosfet_off();
    led_charging_on();
    led_charged_off();
    charging = 1;
}

static void charger_stop() {
    mosfet_on();
    led_charging_off();
    led_charged_on();
    charging = 0;
}

int main(void) {
    float v;    // Current battery voltage

    adc_init(); // time to init?
    led_init();
    mosfet_init();
    uart_init(); // time to init?
    uart_enable_interrupts();

    // setup
    charger_start(); // Charging by default

	while (1) {
        v = map(adc_read(0), ADC_MIN, ADC_MAX, V_MIN, V_MAX);
        if (charging) {
            if (v > V_FLT) {
                // Stop charging
                charger_stop();
            }
        } else {
            if (v <= V_FLT - HYST) {
                // Start charging
                charger_start();
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
                    printf(charging ? "(charging)\n" : "(not charging)\n");
                    break;
            }
        }
    }

    return 0;
}
