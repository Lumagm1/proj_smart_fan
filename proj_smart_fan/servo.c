#include "func.h"
#include <avr/io.h>

void init_SM_IO() {
	// Timer 0 - PWM output = OC0A = PD6
	DDRD |= (1 << PIND6); // Set PD6 = OC0A as an output
}

void initTimer0() {
	TCCR0A |= (1 << COM0A1);					// Non-inverted mode for OC0A
	TCCR0A |= (1 << WGM01) | (1 << WGM00);		// Fast PWM mode									
	TCCR0B |= (1 << CS02) | (1 << CS00);		// Clock prescaler = 1024, freq = 15.6k; PWM freq = 61 Hz
	TCNT0 = 0;									// Initialize counter
}
