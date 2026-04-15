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
	unsigned char prompt8[] = "Button Pressed";
	uint16_t x,y;
	

	lcd_init();  
	init_ADC(0); // Initialize ADC for joystick
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
 
    
    lcd_init();
    init_joystick_ADC();
    init_joystick_button();
    
    while (1) {
        data_joystick_XY(&x, &y);
        Direction direction = get_js_direction(x, y);
    unsigned char *message;
    static unsigned char *last_message = 0; // Store the last displayed message

		
    if (data_joystick_button()) {
        message = prompt8;
    }
    else if (direction == LEFT) {
        message = prompt3;
    }
    else if (direction == RIGHT) {
        message = prompt4;
    }
    else if (direction == UP) {
        message = prompt6;
    }
    else if (direction == DOWN) {
        message = prompt7;
    }
    else {
        message = prompt5;
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
	

