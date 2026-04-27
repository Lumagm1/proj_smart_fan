#include "func.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
	volatile uint8_t channel = 0; // ADC0 for X-axis, ADC1 for Y-axis
	volatile uint16_t x_value = 512; // Global variable to store the ADC value, volatile because it's modified in an ISR
	volatile uint16_t y_value = 512; // Global variable to store the ADC value, volatile because it's modified in an ISR
	volatile uint8_t discard_sample = 0; //
	
	volatile uint8_t tempvalue ; // Global variable to store the ADC value, volatile because it's

void init_ADC(unsigned char identifier) {
	channel = identifier; // Store the input mode (0 for joystick, 1 for temperature sensor)
	if (channel == 0) {
		// Initialize ADC for joystick
		ADMUX = 0;	// use ADC0
	} else if (channel == 1) {
		// Initialize ADC for temperature sensor
		ADMUX = 2;	// use ADC2
	}
	ADMUX = 0;
	ADMUX |= (1 << REFS0);									// Use AVcc as the reference
	ADMUX |= (0 << ADLAR);									// Right-align for 10-bit resolution
	ADCSRA = 0;
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 	// 128 prescale for 16 MHz
	ADCSRA |= (1 << ADATE);  								// Set ADC Auto Trigger Enable (ATE)
	ADCSRB = 0;												// 0 for free running mode
	ADCSRA |= (1 << ADEN);									// Enable the ADC
	ADCSRA |= (1 << ADSC);									// Start the ADC conversion
	ADCSRA |= (1 << ADIE);									// Enable ADC Interrupt
	discard_sample = 0;
	sei();													// Enable global interrupts
}

void stop_ADC() {
	ADCSRA &= ~(1 << ADEN); // Disable the ADC
}

void start_temp_ADC() {
	stop_ADC(); // Stop the joystick ADC if it's running
	init_ADC(1); // Re-initialize ADC for temperature sensor
}

void start_joystick_ADC() {
	stop_ADC(); // Stop the temperature sensor ADC if it's running
	init_ADC(0); // Re-initialize ADC for joystick
}

uint16_t data_joystick_X() {
	return x_value; // Return the latest X-axis value
}

uint16_t data_joystick_Y() {
	return y_value; // Return the latest Y-axis value
}

float read_temp() {
	return temp_monitor(); // Return the latest temperature value
}

float temp_monitor() {

    // Convert ADC reading to millivolts
    // AVcc assumed to be 5.0V = 5000 mV
    float temp_f = tempvalue * (5000.0 / 1024.0);

    // LM35 = 10 mV per degree Celsius
     temp_f = tempvalue / 10.0;

    return temp_f;
}

Direction get_js_direction(uint16_t x, uint16_t y) {
	static Direction last = CENTER; // Store the last direction to avoid rapid changes
	
	//thresholds for direction

	const uint16_t trigger = 768;  // Adjust as needed
	const uint16_t release = 650; // Adjust as needed
	const uint16_t guard = 850; // Adjust as needed

	Direction next = last; // Default to last direction

	if		  ( x < (1023 - trigger) && y > (1023 - guard) && y < guard) {
		next = LEFT;
	} else if ( x > trigger && y > (1023 - guard) && y < guard) {
		next = RIGHT;
	} else if ( y < (1023 - trigger) && x > (1023 - guard) && x < guard) {
		next = UP;
	} else if ( y > trigger && x > (1023 - guard) && x < guard) {
		next = DOWN;
	} else if (last != CENTER) {
		// If joystick is released back to center, only change direction if it was previously not in center
		if (x > (1023 - release) && x < release && y > (1023 - release) && y < release) {
			next = CENTER;
		}
	}
	last = next; // Update last direction
	return next;
}
void data_joystick_XY(uint16_t *x, uint16_t *y) { // Return the latest X and Y values with some averaging
    cli(); // Disable interrupts to safely read shared variables
    uint16_t sx = x_value;
    uint16_t sy = y_value;
	sei(); // Re-enable interrupts after reading

	static uint16_t avg_x = 512, avg_y = 512;
    avg_x = (avg_x * 7 + sx) / 8;
    avg_y = (avg_y * 7 + sy) / 8;
	*x = avg_x;
	*y = avg_y;
}

void init_joystick_button() {
	DDRD &= ~(1 << DDD4); // Set PD4 as input
	PORTD |= (1 << PORTD4); // Enable pull-up resistor on PD4
}

uint8_t data_joystick_button() {
	return (PIND & (1 << PIND4)) == 0; // Return 1 if button is pressed, 0 otherwise
}

// This ISR runs every time an A/D conversion completes
ISR(ADC_vect) {
	if (discard_sample) {
        discard_sample = 0;
        return;
    }
	if(channel == 0){
		x_value = ADCL;	// only read the high value for 10 bit
		x_value |= ((uint16_t)ADCH << 8);
		channel = 1;	// switch to ADC1 for Y-axis
		ADMUX = (ADMUX & 0xF0) | 1;   // switch to ADC1
		discard_sample = 1; // Discard the next sample to allow the channel switch to take effect
	}
	else if (channel == 1){
		y_value = ADCL;	// only read the high value for 10 bit
		y_value |= ((uint16_t)ADCH << 8);
		channel = 0;	// switch back to ADC0 for X-axis
		ADMUX = (ADMUX & 0xF0) | 0;   // switch to ADC0
		discard_sample = 1; // Discard the next sample to allow the channel switch to take effect
	}
	else if (channel == 2) {
		tempvalue = ADCL;	// only read the high value for 8 bit
		tempvalue |= ((uint16_t)ADCH << 8);
	}
}


