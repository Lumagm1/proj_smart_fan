#define F_CPU 16000000UL
#include "func.h"
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define FAN_ANGLE_MIN  0
#define FAN_ANGLE_MAX  4
#define FAN_SPEED_MIN  1
#define FAN_SPEED_MAX  4



static int power_mode = 0;
static int fan_modes = 0;
static int servo_angle_count = 2;
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
        _delay_ms(200);
        char input = wait_input();
        if (input == 'B')
        {
            break;
        }
        else if (input == 'U' || input == 'D')
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
        _delay_ms(200);
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

void auto_mode()
{
    if (power_mode == 1 && fan_modes == 1) 
    {
        adc_init(1); // Switch ADC to temperature sensor mode
        float tempF_float = temp_monitor();
        int tempF = (int)(tempF_float + 0.5);   // round to nearest whole number
        if (tempF <= 70) {
            setFan(25); // 25% speed
            fan_speed_count = 1;
            servo_angle_count = 2;
            servoOscilate(0);
            setServoAngle(90); // 45 degree angle
        } else if (tempF <= 73) {
            setFan(50); // 50% speed
            fan_speed_count = 2;
            servo_angle_count = 2;
            servoOscilate(0);
            setServoAngle(90); // 90 degree angle
        } else if (tempF <= 76) {
            setFan(75); // 75% speed
            fan_speed_count = 3;
            servo_angle_count = 3;
            servoOscilate(0);
            setServoAngle(90); // 135 degree angle
        } else {
            setFan(100); // 100% speed
            fan_speed_count = 4;
            servo_angle_count = 4;
            servoOscilate(1);
            //setServoAngle(180); // 180 degree angle
        }
    } else {
        setFan(0); // Turn off fan
        fan_power = 0;
        setServoAngle(0); // Set servo to default position
    }

}
//page 4
int get_servo_lvl(void)
{
    return servo_angle_count;
}
void fan_angle()
{
    while (1)
    {
        lcd_clear();
        lcd_page();
        _delay_ms(100);
        char input = wait_input();
        if (input == 'B')
        {
            break;
        }
        else if (input == 'D')
        {
            servo_angle_count--;
            if (servo_angle_count < FAN_ANGLE_MIN)
                servo_angle_count = FAN_ANGLE_MAX;
            if (power_mode == 1)
                setServoAngle(servo_angle_count * 45);
        }
        else if (input == 'U')
        {
            servo_angle_count++;
            if (servo_angle_count > FAN_ANGLE_MAX)
                servo_angle_count = FAN_ANGLE_MIN;
            if (power_mode == 1)
                setServoAngle(servo_angle_count * 45);
        }
        lcd_clear();
        lcd_page();
    }
}

//page 5

int get_fan_lvl(void)
{
    return fan_speed_count;
}

void fan_speed()
{
    while (1)
    {
        lcd_clear();
        lcd_page();
        _delay_ms(100);
        char input = wait_input();
        if (input == 'B')
        {
            break;
        }
        else if (input == 'D')
        {
            fan_speed_count--;
            if (fan_speed_count < FAN_SPEED_MIN)
                fan_speed_count = FAN_SPEED_MAX;
            if (power_mode == 1)
                setFan(fan_speed_count * 25);
        }
        else if (input == 'U')
        {
            fan_speed_count++;
            if (fan_speed_count > FAN_SPEED_MAX)
                fan_speed_count = FAN_SPEED_MIN;
            if (power_mode == 1)
                setFan(fan_speed_count * 25);
        }
        lcd_clear();
        lcd_page();
    }
}

//page 6
void fan_temp()
{
    init_ADC(1); // Switch ADC to temperature sensor mode
    while (1)
    {
        lcd_clear();
        lcd_page();
        _delay_ms(200);
        char input = wait_input();
        if (input == 'B')
        {
            init_ADC(0); // Switch back to joystick mode before exiting
            break;
        }
    }
}

