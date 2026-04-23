//nothing

// New change 1 :)


#define F_CPU 16000000UL
#include "func.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void) {
	unsigned char prompt1[] = "Smart Fan";      //Menu 1
	unsigned char prompt2[] = "By Adam n Miko";
    unsigned char prompt3[] = "Power Fan";
    unsigned char prompt4[] = "On";
	unsigned char prompt5[] = "Off";
    unsigned char prompt6[] = "Manual";
    unsigned char prompt7[] = "Auto";
    unsigned char prompt8[] = "Fan Angle";
    unsigned char prompt9[] = "Fan Speed";
    unsigned char prompt10[] = "Temp";
    unsigned char prompt11[] = "Fan Speed";

	uint16_t x,y;
	unsigned char *message = prompt9; // Default message is "Off"
    static unsigned char *last_message = 0; // Store the last displayed message



	lcd_init();  
	init_ADC(0); // Initialize ADC for joystick
    init_joystick_button();
    while (1){
        if (get_page_lvl() == 1)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt1); // Project Smart Fan
            lcd_gotoxy(1, 2);
            lcd_print(prompt2); // Swipe Right ->
        }
        if (get_page_lvl() == 2)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt3); // Power Fan
            lcd_gotoxy(1, 2);
            //lcd_print(prompt4); // On
        }
        if (get_page_lvl() == 3)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt6); // Manual
            lcd_gotoxy(1, 2);
            //  lcd_print (prompt4); // Om

        }
        if (get_page_lvl() == 4)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt7); // Auto
            lcd_gotoxy(1, 2);
            //lcd_print(prompt4); // On
        }
        if (get_page_lvl() == 5)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt8); // Fan Angle
            lcd_gotoxy(1, 2);
            //lcd_print();      //Fan Angle Value
        }
        if (get_page_lvl() == 6)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt9); // Fan Speed
            lcd_gotoxy(1, 2);
            //lcd_print();      //Fan Speed Value
        }
        if (get_page_lvl() == 7)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt10); // Temp
            lcd_gotoxy(1, 2);
            //lcd_print();      //Temp Value
        }
        


    }
    
    
	return 0; 
}   
	

