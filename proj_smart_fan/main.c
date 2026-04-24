//nothing

// New change 1 :)


#define F_CPU 16000000UL
#include "func.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void) {

	uint16_t x,y;
    static unsigned char *last_message = 0; // Store the last displayed message



	lcd_init();  
	init_ADC(0); // Initialize ADC for joystick
    init_joystick_button();
    init_DC_IO();
    while (1){
        lcd_page();
        char input = wait_input();
        if (input == 'B')
        {
            page_action();
            lcd_clear(); 
            lcd_page();
        }
        else if (input == 'R')
        {
            page_nav(1);
        }
        else if (input == 'L')
        {
            page_nav(-1);
        }
    }
    
    
	return 0; 
}   
	

