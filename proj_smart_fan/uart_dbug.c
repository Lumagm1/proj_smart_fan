#define F_CPU 16000000 // Clock Speed
#include "func.h"
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600

void initUART() {
	unsigned int baudrate;
	// Set baud rate: UBRR = [F_CPU/(16*BAUD)] - 1
	baudrate = ((F_CPU/16)/BAUD) - 1;
	UBRR0H = (unsigned char) (baudrate >> 8);
	UBRR0L = (unsigned char) baudrate;
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Enable receiver and transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Set data frame: 8 data bits, 1 stop bit, no parity (8-1-N)
}

void putChar(unsigned char c) {
	UDR0 = c; // Write typed character back to terminal
	while (!(UCSR0A & (1 << TXC0))) ; // Loop until a character is completely transmitted back to terminal
	UCSR0A |= (1 << TXC0); // Clear flag indicating that the character has transmitted
}

unsigned char getChar() {
	unsigned char c;
	while (!(UCSR0A & (1 << RXC0))) ; // Loop until a character is typed
	c = UDR0; // Read typed character
	UCSR0A |= (1 << RXC0); // Clear flag indicating that a character has been received
	return c;
}

void putStr(char *str) {
	unsigned int i = 0;
	while(str[i] != '\0') {
		putChar(str[i]);
		i++;
	}
}


