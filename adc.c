#include <avr/io.h>

#include "adc.h"

void adc_init() {
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // ADC at 62.5KHz sample rate at 4MHz (prescalar at 64)
    ADMUX |= (1 << REFS0); // Set reference voltage to AVCC

    // No MUX values needed to be changed to use ADC0
    //ADMUX |= (1 << MUX0);

    ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode

    ADCSRA |= (1 << ADEN);  // Enable ADC

    ADCSRA |= (1 << ADSC);  // Start A2D Conversions
}

unsigned int adc_read(unsigned char channel) {
	return ADC;
}
