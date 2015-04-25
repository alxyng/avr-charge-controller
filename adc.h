#ifndef ADC_H_
#define ADC_H_

void adc_init(void);

inline unsigned int adc_read(unsigned char channel) {
	return ADC;
}

#endif /* ADC_H_ */
