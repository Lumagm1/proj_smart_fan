#include "func.h"
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

 int fan_count = 1;
 int servo_angle_count = 1;
 int page_count = 1;

unsigned char prompt9[] = "Level:";

void counter_inc(char mode) {
    if (fan_count < 4 && mode == '0')
    {
        fan_count = 1;
    }
    else if (servo_angle_count < 4 && mode == '1')
    {
        servo_angle_count = 1;
    }
    else if (page_count < 8 && mode == '2')
    {
        page_count = 1;
    }
    if (mode == '0')
    {
        fan_count++;
        lcd_gotoxy(1, 2);
        lcd_print(prompt9 + fan_count);
    }
    else if (mode == '1')
    {
        servo_angle_count++;
        lcd_gotoxy(1, 2);
        lcd_print(prompt9 + servo_angle_count);
    }
}

int get_servo_lvl (){
    return servo_angle_count;
}

int get_fan_lvl (){
    return fan_count;
}

void counter_dec(char mode) {
    if ( fan_count < 1)
    {
        fan_count = 4;
    }
    if (servo_angle_count < 1)
    {
        servo_angle_count = 4;
    }
    if (page_count < 1)
    {
        page_count = 8;
    }
    if (mode == '0')
    {
        fan_count--;
        lcd_gotoxy(1, 2);
        lcd_print(prompt9 + fan_count);
    }
    else if (mode == '1')
    {
        servo_angle_count--;
        lcd_gotoxy(1, 2);
        lcd_print(prompt9 + servo_angle_count);
    }
}



void bar_lvl(char mode){
    while (!data_joystick_button())
    {
        Direction last = get_js_direction(data_joystick_X(), data_joystick_Y());
        _delay_ms(500);
        Direction save = get_js_direction(data_joystick_X(), data_joystick_Y());
        if (save == RIGHT && last == CENTER)
        {
            counter_inc(mode);
        }
        else if (save == LEFT && last == CENTER)
        {
            counter_dec(mode);
        }
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
    unsigned char prompt11[] = "Fan Speed";

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


