//nothing

// New change 1 :)
#define F_CPU 16000000L
#include "func.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	initUART();
	init_DC_IO();
	
	while(1) {
		//OCR3B = (getChar()-'0')*64;
	}
}
 