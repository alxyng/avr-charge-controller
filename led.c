#include <avr/io.h>
#include "led.h"

void led_init() {
    DDR_LED |= (1 << DDRPIN_LED_CHARGING); // Set charging LED pin as output
    DDR_LED |= (1 << DDRPIN_LED_CHARGED); // Set charged LED pin as output
}

void led_charging_set(int on) {
    if (on) {
        PORT_LED |= (1 << PIN_LED_CHARGING);
    } else {
        PORT_LED &= ~(1 << PIN_LED_CHARGING);
    }
}

void led_charged_set(int on) {
    if (on) {
        PORT_LED |= (1 << PIN_LED_CHARGED);
    } else {
        PORT_LED &= ~(1 << PIN_LED_CHARGED);
    }
}
