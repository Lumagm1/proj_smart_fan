#include "func.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t fanON = 0;
uint8_t tachCount = 0;

int targetSpeed = 50;
int tachRPM = 0;

int targetAngle = 90;
int currentAngle = 90;

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
	OCR3B = 0;
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

void startFan() {
	fanON = 1;
	OCR3B = targetSpeed * 6.39;
}

void stopFan() {
	fanON = 0;
	OCR3B = 0;
}

void setFan(int target) {
	targetSpeed = target;
	OCR3B = target * 6.39 * fanON;
}

int getTach() {
	return tachRPM;
}


//Servo Functions
void init_Servo_IO() {
	// Timer 1 - PWM output = OC1A = PB1
	DDRB |= (1 << PINB1); // Set PB1 = OC1A as an output
	DDRB |= (1 << PINB5);
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
	targetAngle = angle;
}

ISR(TIMER4_COMPA_vect) {
	tachRPM = 30 * (tachCount);
	tachCount = 0;

	int delta = targetAngle - currentAngle;
	signed int dir = delta / abs(delta);  
	if(abs(delta) > 3) {
		currentAngle += dir * 4;
	} else if (abs(delta) <= 3) {
		currentAngle += delta;
	}
	OCR1A = (int)(500.0 + ((currentAngle / 180.0) * 2000.0));
	PORTB ^= (1 << PINB5);
	/*
	putStr("\r\nFan Speed ");
	putChar((uint8_t)(temp/1000) + '0');
	temp = temp%1000;
	putChar((uint8_t)(temp/100) + '0');
	temp = temp%100;
	putChar((uint8_t)(temp/10) + '0');
	temp = temp%10;
	putChar((uint8_t)(temp) + '0');
	*/
}

ISR(INT1_vect) {
	tachCount++;
}