#include "func.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
	uint8_t channel = 0; // ADC0 for X-axis, ADC1 for Y-axis
	volatile uint8_t x_value; // Global variable to store the ADC value, volatile because it's modified in an ISR
	volatile uint8_t y_value; // Global variable to store the ADC value, volatile because it's modified in an ISR
	volatile uint8_t discard_sample = 0;
void init_joystick_ADC() {
	ADMUX = 1;	// use ADC1
	ADMUX |= (1 << REFS0);									// Use AVcc as the reference
	ADMUX |= (1 << ADLAR);									// Left-align for 8-bit resolution
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 	// 128 prescale for 16 MHz
	ADCSRA |= (1 << ADATE);  								// Set ADC Auto Trigger Enable (ATE)
	ADCSRB = 0;												// 0 for free running mode
	ADCSRA |= (1 << ADEN);									// Enable the ADC
	ADCSRA |= (1 << ADSC);									// Start the ADC conversion
	ADCSRA |= (1 << ADIE);									// Enable ADC Interrupt
	 discard_sample = 0;
	sei();													// Enable global interrupts
	
	
}

uint8_t data_joystick_X() {
	return x_value; // Return the latest X-axis value
}

uint8_t data_joystick_Y() {
	return y_value; // Return the latest Y-axis value
}

void init_joystick_button() {
	DDRD &= ~(1 << DDD3); // Set PB0 as input
	PORTD |= (1 << PORTD3); // Enable pull-up resistor on PB0
}

uint8_t data_joystick_button() {
	return (PIND & (1 << PIND3)) == 0; // Return 1 if button is pressed, 0 otherwise
}

// This ISR runs every time an A/D conversion completes
ISR(ADC_vect) {
	if (discard_sample) {
        discard_sample = 0;
        return;
    }
	if(channel == 0){
		x_value = ADCH;	// only read the high value for 8 bit
		channel = 1;	// switch to ADC1 for Y-axis
		ADMUX = (ADMUX & 0xF0) | 1;   // switch to ADC1
		discard_sample = 1;
	}
	else{
		y_value = ADCH;	// only read the high value for 8 bit
		channel = 0;	// switch back to ADC0 for X-axis
		ADMUX = (ADMUX & 0xF0) | 0;   // switch to ADC0
		discard_sample = 1;
	}
}


