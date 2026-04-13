//#include "func.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

uint8_t tachCount = 0;

void init_DC_IO() {
	DDRD |= (1 << PIND0);	//PWM Output
	DDRD &= ~(1 << PIND2);	//Tach Input
	initTimer3();
}

void initTimer3() {
	TCCR3A |= (1 << COM3A1) | (1 << WGM31);		//OCR3A Clear on match; Fast PWM ICR3 Mode
	TCCR3B |= (1 << WGM32)  | (1 << WGM33) | (1 << CS30);	//No Prescaler
	ICR3 = 639; // f_clk/f_pwm - 1 = 639 (25khz Clock)
	OCR3A = 200;
	TCNT3 = 0;	// Start Clock
}

ISR(TIMER3_COMPA_vect) {
	
}

ISR(INT0_vect) {
	
}