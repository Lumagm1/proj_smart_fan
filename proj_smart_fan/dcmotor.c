//#include "func.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define MAX_RPM 3000
#define MIN_RPM 650

uint8_t tachCount = 0;
uint8_t tachRPM = 0;

void init_DC_IO() {
	DDRD |= (1 << PIND0);	//PWM Output
	DDRD &= ~(1 << PIND2);	//Tach Input
	initTimer3();
	initTimer4();
	sei();
}

void initTimer3() {
	TCCR3A |= (1 << COM3A1) | (1 << WGM31);					//OCR3A Clear on match; Fast PWM ICR3 Mode
	TCCR3B |= (1 << WGM32)  | (1 << WGM33) | (1 << CS30);	//No Prescaler
	ICR3 = 639;												// f_cpu/f_pwm - 1 = 639 (25khz Clock)
	OCR3A = 200;
	TCNT3 = 0;	// Start Clock
}

void initTimer4() {
	TCCR4A |= (1 << COM4A0);								//OCR1A Toggle on match
	TCCR4B |= (1 << WGM42) | (1 << CS40) | (1 << CS42) ;	// /1024 Prescaler; 
	OCR4A = 15624; // f_cpu/1024 - 1 = 15624
	TCNT4 = 0;	// Start Clock
}


ISR(TIMER4_COMPA_vect) {
	tachRPM = 30 * (tachCount);
	tachCount = 0;
}

ISR(INT0_vect) {
	tachCount++;
}