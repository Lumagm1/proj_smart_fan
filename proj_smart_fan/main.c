//nothing

// New change 1 :)

#include <stdint.h>
#define F_CPU 16000000UL
#include "func.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	unsigned char prompt1[] = "Menu";
	unsigned char prompt2[] = "Swipe Right";
	unsigned char prompt3[] = "Left";
	unsigned char prompt4[] = "Right";
	unsigned char prompt5[] = "Center";
	unsigned char prompt6[] = "Up";
	unsigned char prompt7[] = "Down";
	unsigned char prompt8[] = "On";
    unsigned char prompt9[] = "Off";
	uint16_t x,y;
	

	lcd_init();  
	init_ADC(0); // Initialize ADC for joystick
    init_joystick_button();
    int check = 1;
    while (check) {
        data_joystick_XY(&x, &y);
        Direction direction = get_js_direction(x, y);
        lcd_gotoxy(1,1);  
	    lcd_print(prompt1);  
	    lcd_gotoxy(1,2);  
	    lcd_print(prompt2); 
        if (direction == RIGHT ) {
            check = 0; // Prevent re-entering the menu
            break; // Exit the loop to enter the menu
        }
    }
 
    
\
    
    
    while (1) {
        data_joystick_XY(&x, &y);
        Direction direction = get_js_direction(x, y);
    unsigned char *message;
    static unsigned char *last_message = 0; // Store the last displayed message

		
    if (data_joystick_button()) { // if the button is pressed 
        lcd_clear();
        lcd_gotoxy(1,1);
        lcd_print(message);
        message = prompt8;
        _delay_ms(500); // Debounce delay
    } 

    if (!data_joystick_button()) { // If the button is released
        lcd_clear();
        lcd_gotoxy(1,1);
        lcd_print(message);
        message = prompt9;
        _delay_ms(500); // Debounce delay
    }
    
    if (message != last_message) {
        lcd_clear();
        lcd_gotoxy(1,1);
        lcd_print(message);
        last_message = message;
    }
    _delay_ms(100);
    }
	return 0; 
}   
	

