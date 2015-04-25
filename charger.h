#define PORT_MOSFET		PORTB
#define DDR_MOSFET		DDRB

#define PIN_MOSFET		PORTB1
#define DDRPIN_MOSFET	DDB1

inline void charger_init(void) {
	DDR_MOSFET |= (1 << DDRPIN_MOSFET); // Set MOSFET pin as output
}

inline void charger_start(void) {
	PORT_MOSFET |= (1 << PIN_MOSFET);		// Turn MOSFET on
}

inline void charger_stop(void) {
	PORT_MOSFET &= ~(1 << PIN_MOSFET);		// Turn MOSFET off
}
