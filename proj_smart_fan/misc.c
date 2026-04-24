#include "func.h"
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define PAGE_MIN 1
#define PAGE_MAX 6

 
 static int page_count = 1;



void page_nav(int count)
{
    page_count += count;
    if (page_count < PAGE_MIN)
    {
        page_count = PAGE_MAX;
    }
    if (page_count > PAGE_MAX)
    {
        page_count = PAGE_MIN;
    }
}

int get_page_num(void)
{
    return page_count;
}










char wait_input(void) {
    Direction prev = CENTER;
    while (1) {
        if (data_joystick_button()) {
            _delay_ms(50);
            while (data_joystick_button());
            return 'B';
        }
        Direction cur = get_js_direction(data_joystick_X(), data_joystick_Y());
        if (prev == CENTER && cur == RIGHT) return 'R';
        if (prev == CENTER && cur == LEFT)  return 'L';
        prev = cur;
        _delay_ms(30);
    }
}
void lcd_page()
{
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
    unsigned char prompt11[] = "RPM Monitor";
    unsigned char prompt12[] = "LVL";

     if (get_page_num() == 1)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt1); // Project Smart Fan
            lcd_gotoxy(1, 2);
            lcd_print(prompt2); // Swipe Right ->
        }
        if (get_page_num() == 2)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt3); // Power Fan
            lcd_gotoxy(1, 2);
            lcd_print(get_power_mode() ? prompt4:prompt5);
        }
        if (get_page_num() == 3)
        {
            lcd_gotoxy(1, 1);
            lcd_print(get_fan_mode() ? prompt6:prompt7); // Manual or auto
            lcd_gotoxy(1, 2);
            lcd_print(prompt4);
             
        }
        if (get_page_num() == 4)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt8); // Fan Angle
            lcd_gotoxy(1, 2);
            lcd_print(prompt12);      //Fan Angle Value
        }
        if (get_page_num() == 5)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt9); // Fan Speed
            lcd_gotoxy(1, 2);
            lcd_print(prompt12);         //Fan Speed Value
        }
        if (get_page_num() == 6)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt10); // Temp
            lcd_gotoxy(1, 2);
            lcd_print(prompt12);      //Temp Value
        }
        if (get_page_num() == 7)
        {
            lcd_gotoxy(1, 1);
            lcd_print(prompt11); // Temp
            lcd_gotoxy(1, 2);
            lcd_print(prompt12);      //Temp Value
        }
}



void page_action()
{
    switch(page_count)
    {
        case 1:
            break;
        case 2:
            fan_power();
        case 3:
            fan_mode();
        case 4:
            fan_angle();
        case 5:
            fan_speed();
        case 6:
            fan_temp();
        default:
            break;
    }
}








