#include <avr/io.h>
#include "led.h"

void led_init() {
    DDR_LED |= (1 << DDRPIN_CHARGING_LED); // Set charging LED pin as output
    DDR_LED |= (1 << DDRPIN_CHARGED_LED); // Set charged LED pin as output
}

void led_set_charging(int on) {
    if (on) {
        PORT_LED |= (1 << PIN_CHARGING_LED);
    } else {
        PORT_LED &= ~(1 << PIN_CHARGING_LED);
    }
}

void led_set_charged(int on) {
    if (on) {
        PORT_LED |= (1 << PIN_CHARGED_LED);
    } else {
        PORT_LED &= ~(1 << PIN_CHARGED_LED);
    }
}
