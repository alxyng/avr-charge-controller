#include <stdio.h>

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#ifndef BAUD
#define BAUD 9600       // 9600bps
#endif

#include "uart.h"

#include <util/delay.h>

#define LEDOUT PORTC3
#define LEDPORT PORTC
#define LEDDDR DDRC
#define LEDDDRPIN DDC3

#define PORT_LED    PORTC
#define DDR_LED     DDRC

#define PIN_CHARGING_LED    PORTC3
#define DDRPIN_CHARGING_LED DDC3

#define PIN_CHARGED_LED    PORTC2
#define DDRPIN_CHARGED_LED DDC2

//#define LEDOUT PORTD5
//#define LEDPORT PORTD
//#define LEDDDR DDRD
//#define LEDDDRPIN DDD5

// _delay_ms uses a floating point datatype if you call
// that function in many places in your code then it becomes
// very fat. An integer is enough for us:
//
// delay x milliseconds:
void delay_ms(unsigned int xms)
{
        while(xms){
                _delay_ms(0.96);
                xms--;
        }
}

void configure_and_start_adc() {
    /* Default values are 0 for these 3 bits so dont need manually setting
    ADCSRA &= ~(1 << ADPS2);
    ADCSRA &= ~(1 << ADPS1);
    ADCSRA &= ~(1 << ADPS0);
    */

    ADCSRA |= (1 << ADPS2); // ADC at 62.5KHz sample rate at 1MHz (prescalar at 16)
    ADMUX |= (1 << REFS0); // Set reference voltage to AVCC
    ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

    // No MUX values needed to be changed to use ADC0
    ADMUX |= MUX1;

    ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode

    ADCSRA |= (1 << ADEN);  // Enable ADC

    ADCSRA |= (1 << ADSC);  // Start A2D Conversions
}

void configure_and_start_pwm() {
    // Port D5 as output
    DDRD |= (1 << 5);
}

void charging_pin_configure() {
    DDR_LED |= (1 << DDRPIN_CHARGING_LED); // Set charging LED pin as output
    DDR_LED |= (1 << DDRPIN_CHARGED_LED); // Set charged LED pin as output
}

void set_charging_led(int on) {
    if (on) {
        PORT_LED |= (1 << PIN_CHARGING_LED);
    } else {
        PORT_LED &= ~(1 << PIN_CHARGING_LED);
    }
}

void set_charged_led(int on) {
    if (on) {
        PORT_LED |= (1 << PIN_CHARGED_LED);
    } else {
        PORT_LED &= ~(1 << PIN_CHARGED_LED);
    }
}


int main() {
    /* enable pin as output */
    //LEDDDR|= (1<<LEDDDRPIN);

    charging_pin_configure();

    //configure_and_start_adc();
    //configure_and_start_pwm();

    //int charging = 1;
/*
    DDRB=0x08;

    OCR2=0x1A; // 256/10=25,6 26 in hex = 1A;

    //TCCR2=0x6E; // 256 prescaler

    TCCR2 |= ((1 << CS22) | (1 << CS21)) ;
*/
/*
    DDRB = 0x06;                      // Set Port PB1 and PB2 as Output

    TCCR1A = (1<<WGM10)|(1<<COM1A1)   // Set up the two Control registers of Timer1.
            |(1<<COM1B1);             // Wave Form Generation is Fast PWM 8 Bit,
    TCCR1B = (1<<WGM12)|(1<<CS10);     // OC1A and OC1B are cleared on compare match
            //|(1<<CS10);               // and set at BOTTOM. Clock Prescaler is 1024.

    OCR1A = 63;                       // Dutycycle of OC1A = 25%
    OCR1B = 127;                      // Dutycycle of OC1B = 50%
*/
    //int direction = 1;
	while (1) {
        /*
        if (direction) {
            OCR1B++;
            if (OCR1B == 255) {
                direction = 0;
            }
        } else {
            OCR1B--;
            if (OCR1B == 0) {
                direction = 1;
            }
        }
        _delay_ms(10);
        */

        //set_charging_led(1);
        //set_charging_led(0);

        /*
        LEDPORT|= (1<<LEDOUT);
        delay_ms(ADCH / 15);
        LEDPORT &= ~(1<<LEDOUT);
        delay_ms((255 - ADCH) / 15);
        */
/*
        set_charging_led(charging);
        set_charged_led(!charging);

        charging = !charging;

        _delay_ms(1000);
*/
/*
        if (ADCH < 128) {
            PORT_LED  &= ~(1 << PIN_CHARGING_LED);
        } else {
            PORT_LED |= (1 << PIN_CHARGING_LED);
        }
*/
        //OCR1B = 127;
        //OCR1B = ADCH;

    	/* led on, pin=0 */
    	//LEDPORT &= ~(1<<LEDOUT);
    	//_delay_ms(25);
    	/* set output to 5V, LED off */
    	//LEDPORT|= (1<<LEDOUT);
    	//_delay_ms(25);
    }

    return 0;
}
