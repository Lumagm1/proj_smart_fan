#include "func.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

uint8_t tachCount = 0;

void init_DC_IO() {
	DDRB |= (1 << PINB3);	//PWM Output
	DDRD &= ~(1 << PIND2);	//Tach Input
	initTimer2();
}

void initTimer2() {
	TCCR2A |= (1 << COM2A0) | (1 << WGM20) | (1 << WGM21);
	TCCR2B |= 
}

ISR(TIMER2_COMPA_vect) {
	
}

ISR(INT0_vect) {
	
}