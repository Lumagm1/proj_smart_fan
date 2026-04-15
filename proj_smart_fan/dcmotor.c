#include "func.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define MAX_RPM 3000
#define MIN_RPM 650

uint8_t tachCount = 0;
int tachRPM = 0;
int temp = 0;

void init_DC_IO() {
	DDRD |= (1 << PIND2);	//PWM Output
	PORTD |= (1 << PIND2);
	DDRD &= ~(1 << PIND3);	//Tach Input
	initTimer3();
	initTimer4();
	
	PORTD |= (1 << PIND3);
	// Configure INT1 to trigger on falling edge
	EICRA |= (1 << ISC11);
	EICRA &= ~(1 << ISC10);

	// Enable INT1 interrupt
	EIMSK |= (1 << INT1);
	
	sei();
}

void initTimer3() {
	TCCR3A = (1 << COM3B1) | (1 << WGM31);					//OCR3B Clear on match; Fast PWM ICR3 Mode
	TCCR3B = (1 << WGM32)  | (1 << WGM33) | (1 << CS30);	//No Prescaler
	ICR3 = 639;												// f_cpu/f_pwm - 1 = 639 (25khz Clock)
	OCR3B = 200;
	TCNT3 = 0;	// Start Clock
}

void initTimer4() {
	TCCR4A |= (1 << COM4A0);								//OCR1A Toggle on match
	TCCR4B |= (1 << WGM42) | (1 << CS40) | (1 << CS42) ;	// /1024 Prescaler; 
	TIFR4 |= (1 << OCF4A);
	TIMSK4 |= (1 << OCIE4A);
	OCR4A = 15624; // f_cpu/1024 - 1 = 15624
	TCNT4 = 0;	// Start Clock
}


ISR(TIMER4_COMPA_vect) {
	tachRPM = 30 * (tachCount);
	tachCount = 0;

	temp = tachRPM;
	putStr("\r\nFan Speed ");
	putChar((uint8_t)(temp/1000) + '0');
	temp = temp%1000;
	putChar((uint8_t)(temp/100) + '0');
	temp = temp%100;
	putChar((uint8_t)(temp/10) + '0');
	temp = temp%10;
	putChar((uint8_t)(temp) + '0');
}

ISR(INT1_vect) {
	tachCount++;
}