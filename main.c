//nothing

// New change 1 :)
/*
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
	const uint8_t left_threshold = 50; // Adjust as needed
	const uint8_t right_threshold = 200; // Adjust as needed
	
	

	lcd_init();  
	init_joystick_ADC();
	lcd_gotoxy(1,1);  
	lcd_print(prompt1);  
	lcd_gotoxy(1,2);  
	lcd_print(prompt2);  
	_delay_ms(264);
	
	unsigned char *last_message = 0;

	while (1) {
    uint8_t x = data_joystick_X();
    uint8_t y = data_joystick_Y();
    unsigned char *message;
		
    if (data_joystick_button()) {
        message = prompt8;
    }
    else if (x < left_threshold && y >= left_threshold && y <= right_threshold) {
        message = prompt3;
    }
    else if (x > right_threshold && y >= left_threshold && y <= right_threshold) {
        message = prompt4;
    }
    else if (y < left_threshold && x >= left_threshold && x <= right_threshold) {
        message = prompt6;
    }
    else if (y > right_threshold && x >= left_threshold && x <= right_threshold) {
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
	*/

	#include <stdint.h>
#include <stdio.h>
#define F_CPU 16000000UL
#include "func.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    unsigned char prompt_left[]   = "Left            ";
    unsigned char prompt_right[]  = "Right           ";
    unsigned char prompt_center[] = "Center          ";
    unsigned char prompt_up[]     = "Up              ";
    unsigned char prompt_down[]   = "Down            ";
    unsigned char prompt_press[]  = "Pressed         ";

    const uint8_t left_threshold  = 50;
    const uint8_t right_threshold = 200;

    char line2[17];
    unsigned char *message = prompt_center;
    unsigned char *last_message = 0;

    lcd_init();
    init_joystick_ADC();
    init_joystick_button();

    while (1) {
        uint8_t x = data_joystick_X();
        uint8_t y = data_joystick_Y();

        if (data_joystick_button()) {
            message = prompt_press;
        }
        else if (x < left_threshold && y >= left_threshold && y <= right_threshold) {
            message = prompt_left;
        }
        else if (x > right_threshold && y >= left_threshold && y <= right_threshold) {
            message = prompt_right;
        }
        else if (y < left_threshold && x >= left_threshold && x <= right_threshold) {
            message = prompt_up;
        }
        else if (y > right_threshold && x >= left_threshold && x <= right_threshold) {
            message = prompt_down;
        }
        else {
            message = prompt_center;
        }

        if (message != last_message) {
            lcd_gotoxy(1,1);
            lcd_print(message);
            last_message = message;
        }

        snprintf(line2, sizeof(line2), "X:%3u Y:%3u   ", x, y);
        lcd_gotoxy(1,2);
        lcd_print((unsigned char *)line2);

        _delay_ms(100);
    }

    return 0;
}