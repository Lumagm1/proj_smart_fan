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
typedef enum {UP,DOWN,LEFT,RIGHT,CENTER
} Direction;
void init_ADC(unsigned char identifier);
void stop_ADC();
void start_temp_ADC();
void start_joystick_ADC();
uint16_t data_joystick_X();
uint16_t data_joystick_Y();
Direction get_js_direction(uint16_t x, uint16_t y);
void data_joystick_XY(uint16_t *x, uint16_t *y);
void init_joystick_button();
uint8_t data_joystick_button();


// Temperature Sensor
//void init_TS_IO();

// Servo Motor 
void init_Servo_IO();
void initTimer1();
void setServoAngle(double angle);

//DC Fan Motor
void init_DC_IO();
void initTimer3();
void initTimer4();
int DC_Fan_data();

void startFan();
void stopFan();
void setFan();


void initUART();
unsigned char getChar();
void putChar(unsigned char c);
void putStr(char *str);



 void i2c(unsigned char data, unsigned char address);
 void i2c_init();
 void i2c_start();
 void i2c_address(unsigned char data);
 void i2c_data(unsigned char data);
 void i2c_stop();

 //misc functions

 char wait_input(void);
 int get_servo_lvl();
 int get_fan_lvl();
 void lcd_page();
 void page_nav(int count);
 void page_action();
 int get_page_num(void);
 int get_power_mode();
 int get_fan_mode(void);
 int get_fan_speed(void);


// Page Functions
void fan_power();   // PAGE 2
void fan_mode();    // PAGE 3
void fan_angle();   // PAGE 4
void fan_speed();   // PAGE 5
void fan_temp();    // PAGE 6
void fan_speed_monitor();   // PAGE 7


 

#endif
