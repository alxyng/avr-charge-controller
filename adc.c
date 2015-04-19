#include <avr/io.h>

void adc_init() {
    ADCSRA |= (1 << ADPS2) | (1 << ADPS2); // ADC at 125KHz sample rate at 8MHz (prescalar at 64)
    ADMUX |= (1 << REFS0); // Set reference voltage to AVCC

    //ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

    // No MUX values needed to be changed to use ADC0
    //ADMUX |= (1 << MUX0);

    ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode

    ADCSRA |= (1 << ADEN);  // Enable ADC

    ADCSRA |= (1 << ADSC);  // Start A2D Conversions
}

unsigned int adc_read(unsigned char channel) {
	return (ADCH << 8) | ADCL;
}
