#ifndef FUNC_H
#define FUNC_H

// your declarations go here

#define LCD_DPRT PORTD // LCD DATA PORT 
#define LCD_DDDR DDRD  // LCD DATA DDR 

#define LCD_CPRT PORTB // LCD CONTROL PORT 
#define LCD_CDDR DDRB  // LCD CONTOL DDR 

#define LCD_RS  0      // LCD RS  
#define LCD_RW  1      // LCD RW  
#define LCD_EN  2      // LCD EN

// Function prototypes For Servo Motor
#define LCD_DPRT PORTD // LCD DATA PORT 
#define LCD_DDDR DDRD  // LCD DATA DDR 

#define LCD_CPRT PORTB // LCD CONTROL PORT 
#define LCD_CDDR DDRB  // LCD CONTOL DDR 

#define LCD_RS  0      // LCD RS  
#define LCD_RW  1      // LCD RW  
#define LCD_EN  2      // LCD EN

// Function prototypes

// LCD Functions
void init_LCD_IO();
void blinkLED();
void lcdCommanda (unsigned char cmnd);
void lcdData(unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char x, unsigned char y);  
void lcd_print(unsigned char * str);
void lcd_i2c(unsigned char data);

// Joystick Functions
void init_joystick_ADC();

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
void i2c_write(unsigned char data);
unsigned char i2c_read_ack();
unsigned char i2c_read_nack();
void i2c_stop();


#endif