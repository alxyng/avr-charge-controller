#define PORT_MOSFET		PORTB
#define DDR_MOSFET		DDRB

#define PIN_MOSFET		PORTB1
#define DDRPIN_MOSFET	DDB1

inline void mosfet_init(void) {
	DDR_MOSFET |= (1 << DDRPIN_MOSFET);		// Set MOSFET pin as output
}

inline void mosfet_on(void) {
	PORT_MOSFET |= (1 << PIN_MOSFET);		// Turn MOSFET on
}

inline void mosfet_off(void) {
	PORT_MOSFET &= ~(1 << PIN_MOSFET);		// Turn MOSFET off
}
