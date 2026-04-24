#include "func.h"
#include <avr/io.h>

void init_Servo_IO() {
	// Timer 1 - PWM output = OC1A = PB1
	DDRB |= (1 << PINB1); // Set PB1 = OC1A as an output
	initTimer1();
}

void initTimer1() {
	TCCR1A |= (1 << COM1A1);	// Non-inverted mode for OC1A
	TCCR1B |= (1 << WGM13);		// Phase/Frequency Correct mode for OC1A								
	TCCR1B |= (1 << CS11);		// Clock prescaler = 8, PWM freq = 50Hz
	ICR1 = 20000;				// TOP value for 50Hz PWM
	OCR1A = 500;				// Initial duty cycle (0.5ms pulse width = 0 Degrees)
	TCNT1 = 0;					// Initialize counter
}

void setServoAngle(double angle) {
	if (angle < 0) angle = 0;
	if (angle > 180) angle = 180;
	
	// Map angle (0-180) to pulse width (500-2500 microseconds)
	int pulseWidth = 500.0 + ((angle / 180.0) * 2000.0); 
	OCR1A = pulseWidth;
}