#ifndef LED_H_
#define LED_H_

#define PORT_LED    PORTC
#define DDR_LED     DDRC

#define PIN_CHARGING_LED    PORTC2
#define DDRPIN_CHARGING_LED DDC2

#define PIN_CHARGED_LED    PORTC5
#define DDRPIN_CHARGED_LED DDC5

void led_init();
void led_set_charging(int on);
void led_set_charged(int on);

#endif
