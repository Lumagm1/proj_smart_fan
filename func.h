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

// Function prototypes

// LCD Functions
void init_LCD_IO();
void blinkLED();
void lcdCommanda (unsigned char cmnd);
void lcdData(unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char x, unsigned char y);  
void lcd_print(unsigned char * str);

// Joystick Functions
void initADC();

// Temperature Sensor
void init_TS_IO();

// Servo Motor 
void init_SM_IO();
void initTimer0();

//DC Fan Motor
void initIO();
void initTimer0();
void initUART();

#endif