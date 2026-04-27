//nothing

// New change 1 :)


#define F_CPU 16000000UL
#include "func.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void) {
	lcd_init();  
	init_ADC(0); // Initialize ADC for joystick
    init_joystick_button();
    init_DC_IO();
    init_Servo_IO();
    while (1){
        lcd_clear();
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
        _delay_ms(200);
    }
    
    
	return 0; 
}   
	

