#ifndef FUNC_H
#define FUNC_H

// your declarations go here

#include <stdint.h>
#define LCD_RS (1 << 0)
#define LCD_RW (1 << 1)
#define LCD_EN (1 << 2)
#define LCD_BL (1 << 3)

// Function prototypes

// LCD Functions
void lcdCommanda (unsigned char cmnd);
void lcdData(unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char x, unsigned char y);  
void lcd_print(unsigned char * str);
void lcd_clear();

void lcd_expander_write(int data);
void pulse_enable(int data);
void lcd_write4bits(int data);
void lcd_send(int value,int rs);


// Joystick Functions
typedef enum {
    UP,DOWN,LEFT,RIGHT,CENTER
} Direction;
void init_joystick_ADC();
uint8_t data_joystick_X();
uint8_t data_joystick_Y();
Direction get_js_diretion(uint8_t x, uint8_t y);
void data_joystick_XY(uint8_t *x, uint8_t *y);
void init_joystick_button();
uint8_t data_joystick_button();

// Temperature Sensor
void init_TS_IO();

// Servo Motor 
void init_SM_IO();
void initTimer0();

//DC Fan Motor
void init_DC_IO();
void initTimer1();

void i2c(unsigned char data, unsigned char address);
void i2c_init();
void i2c_start();
void i2c_address(unsigned char data);
void i2c_data(unsigned char data);
void i2c_stop();


#endif