#ifndef LED_H_
#define LED_H_

#define PORT_LED    PORTC
#define DDR_LED     DDRC

#define PIN_LED_CHARGING    PORTC2
#define DDRPIN_LED_CHARGING DDC2

#define PIN_LED_CHARGED    PORTC5
#define DDRPIN_LED_CHARGED DDC5

void led_init();
void led_charging_set(int on);
void led_charged_set(int on);

#endif /* LED_H_ */
