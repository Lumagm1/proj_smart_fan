#include "func.h"
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define FAN_ANGLE_MIN  1
#define FAN_ANGLE_MAX  4
#define FAN_SPEED_MIN  1
#define FAN_SPEED_MAX  4



static int power_mode = 0;
static int fan_modes = 0;
static int servo_angle_count = 1;
static int page_count = 1;
static int fan_speed_count = 1;


// page 2
int get_power_mode()
{
    return power_mode;
}
void fan_power()
{
    while (1)
    {
        lcd_clear();
        lcd_page();
        char input = wait_input();
        if (input == 'B')
        {
            break;
        }
        else if (input == 'L' || input == 'R')
        {
            power_mode = !power_mode;
            if (power_mode == 1)
            {
                startFan();
            }else{
                stopFan();
            }
        }
    }
}


// page 3
int get_fan_mode(){
    return fan_modes;
}
void fan_mode()
{
    while (1)
    {
        lcd_clear();
        lcd_page();
        char input = wait_input();
        if (input == 'B')
        {
            break;
        }
        else if (input == 'L' || input == 'R')
        {
            fan_modes = !fan_modes;
        }
    }
}

//page 4

void fan_angle()
{
    while (1)
    {
        lcd_clear();
        lcd_page();
        char input = wait_input();
        if (input == 'B')
        {
            break;
        }
        else if (input == 'L')
        {
            servo_angle_count--;
            if (servo_angle_count < FAN_ANGLE_MIN)
            {
                servo_angle_count = FAN_ANGLE_MAX;
            }
            else if (servo_angle_count >  FAN_ANGLE_MAX)
            {
                servo_angle_count = FAN_ANGLE_MIN;
            }
        }
    }
}

void fan_speed()
{
    while (1)
    {
        lcd_clear();
        lcd_page();
        char input = wait_input();
        if (input == 'B')
        {
            break;
        }
        else if (input == 'L')
        {
            fan_speed_count--;
            if (fan_speed_count < FAN_SPEED_MIN)
            {
                fan_speed_count = FAN_SPEED_MAX;
            }
            else if (fan_speed_count >  FAN_SPEED_MAX)
            {
                fan_speed_count = FAN_SPEED_MIN;
            }
        }
    }
}


