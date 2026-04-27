#define F_CPU 16000000UL
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
        _delay_ms(2000);
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
        _delay_ms(2000);
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
        _delay_ms(2000);
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
                if (power_mode == 1) {
                    setServoAngle(servo_angle_count * 45); // Assuming servo angle levels correspond to 45, 90, 135, 180 degrees
                }
                // put servo angle function here with servo_angle_count as input/argument
            }
            else if (servo_angle_count >  FAN_ANGLE_MAX)
            {
                servo_angle_count = FAN_ANGLE_MIN;
                if (power_mode == 1) {
                    setServoAngle(servo_angle_count * 45); // Assuming servo angle levels correspond to 45, 90, 135, 180 degrees
                }
                // put servo angle function here with servo_angle_count as input/argument
            }
        }
    }
}

//page 5

int get_fan_speed(void)
{
    return fan_speed_count;
}

void fan_speed()
{
    while (1)
    {
        lcd_clear();
        lcd_page();
        _delay_ms(2000);
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
                if (power_mode == 1) {
                    setFan(fan_speed_count * 25); // Assuming fan speed levels correspond to 25%, 50%, 75%, 100%
                }
                // put fan speed function here with fan_speed_count as input/argument
            }
            else if (fan_speed_count >  FAN_SPEED_MAX)
            {
                fan_speed_count = FAN_SPEED_MIN;
                if (power_mode == 1) {
                    setFan(fan_speed_count * 25); // Assuming fan speed levels correspond to 25%, 50%, 75%, 100%
                }
                // put fan speed function here with fan_speed_count as input/argument
            }
        }
    }
}

void fan_temp()
{
    init_ADC(1); // Switch ADC to temperature sensor mode
    while (1)
    {
        lcd_clear();
        lcd_page();
        _delay_ms(2000);
        char input = wait_input();
        if (input == 'B')
        {
            init_ADC(0); // Switch back to joystick mode before exiting
            break;
        }
    }
}

