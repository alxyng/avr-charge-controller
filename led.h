#ifndef LED_H_
#define LED_H_

#define PORT_LED    PORTC
#define DDR_LED     DDRC

#define PIN_LED_CHARGING    PORTC2
#define DDRPIN_LED_CHARGING DDC2

#define PIN_LED_CHARGED    PORTC5
#define DDRPIN_LED_CHARGED DDC5

inline void led_init(void) {
    DDR_LED |= (1 << DDRPIN_LED_CHARGING); // Set charging LED pin as output
    DDR_LED |= (1 << DDRPIN_LED_CHARGED); // Set charged LED pin as output
}

inline void led_charging_on(void) {
    PORT_LED |= (1 << PIN_LED_CHARGING);
}

inline void led_charging_off(void) {
    PORT_LED &= ~(1 << PIN_LED_CHARGING);
}

inline void led_charged_on(void) {
    PORT_LED |= (1 << PIN_LED_CHARGED);
}

inline void led_charged_off(void) {
    PORT_LED &= ~(1 << PIN_LED_CHARGED);
}

#endif /* LED_H_ */
