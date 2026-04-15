#ifndef FUNC_H
#define FUNC_H

// your declarations go here

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

void lcd_expander_write(int data);
void pulse_enable(int data);
void lcd_write4bits(int data);
void lcd_send(int value,int rs);


// Joystick Functions
void init_joystick_ADC();

// Temperature Sensor
void init_TS_IO();

// Servo Motor 
void init_SM_IO();
void initTimer0();

//DC Fan Motor
void init_DC_IO();
void initTimer3();
void initTimer4();

//UART Debug
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


#endif