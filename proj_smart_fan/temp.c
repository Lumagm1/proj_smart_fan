#include "func.h"
#include <avr/io.h>

// void init_joystick_ADC() {
// 	ADMUX = 0;	// use ADC0
// 	ADMUX |= (1 << REFS0);									// Use AVcc as the reference
// 	ADMUX |= (1 << ADLAR);									// Left-align for 8-bit resolution
// 	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 	// 128 prescale for 16 MHz
// 	ADCSRA |= (1 << ADATE);  								// Set ADC Auto Trigger Enable (ATE)
// 	ADCSRB = 0;												// 0 for free running mode
// 	ADCSRA |= (1 << ADEN);									// Enable the ADC
// 	ADCSRA |= (1 << ADSC);									// Start the ADC conversion
// 	ADCSRA |= (1 << ADIE);									// Enable ADC Interrupt
// 	sei();													// Enable global interrupts
// 
// }
// 
// // This ISR runs every time an A/D conversion completes
// ISR(ADC_vect) {
// 	ADCvalue = ADCH;	// only read the high value for 8 bit
// }

