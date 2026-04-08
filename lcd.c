#include "func.h"
#include <avr/io.h>

#define LCD_ADDR 0x27 // I2C address of the LCD

void lcdCommanda (unsigned char cmnd) {  
	LCD_DPRT = cmnd;				// Send cmnd to data port  
	
	LCD_CPRT &= ~(1 << LCD_RS);		// RS = 0 for command  
	LCD_CPRT &= ~(1 << LCD_RW);		// RW = 0 for write   
	LCD_CPRT |=  (1 << LCD_EN);		// EN = 1 (E = EN) for H-to-L pulse  
	_delay_us(1);					// Wait to make enable wide  
	LCD_CPRT &= ~(1 << LCD_EN);		// EN = 0 for H-to_L pulse  
	_delay_us(100);					// Wait to make enable wide 
} 
 
void lcdData(unsigned char data) {  
	LCD_DPRT = data;				// Send data to data port 
	LCD_CPRT |=  (1 << LCD_RS);		// RS = 1 for data  
	LCD_CPRT &= ~(1 << LCD_RW);		// RW = 0 for write   
	LCD_CPRT |=  (1 << LCD_EN);		// EN = 1 (E = EN) for H-to-L pulse  
	_delay_us(1);					// Wait to make enable wide  
	LCD_CPRT &= ~(1 << LCD_EN);		// EN = 0 for H-to_L pulse  
	_delay_us(100);					// Wait to make enable wide  
} 

void lcd_init() {  
	LCD_DDDR = 0xFF;  
	LCD_CDDR = 0xFF;    
	LCD_CPRT &= ~(1 << LCD_EN);		// LCD_EN = 0  
	_delay_us(2000);    
	// Wait for init  
	lcdCommanda(0x38);				// Initialize LCD 2 line, 5x7 characters 
	lcdCommanda(0x0E);				// Display on, cursor on  
	lcdCommanda(0x01);				// Clear LCD  
	_delay_us(2000);				// Wait  
	lcdCommanda(0x06);				// Shift cursor right after display char.
} 
 
void lcd_gotoxy(unsigned char x, unsigned char y) {  
	unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};   
	
	lcdCommanda(firstCharAdr[y-1] + x -1);  
	_delay_us(100); 
} 
 
void lcd_print(unsigned char * str) {  
	unsigned char i = 0;  
	
	while (str[i]!=0)  {   
		lcdData(str[i]); 
		i++;  
	}
} 



void lcd_i2c(unsigned char data) {
	i2c_init();
	i2c_start();
	i2c_write((LCD_ADDR << 1) | 0); // Write address
	i2c_write(data); // Write data
	i2c_stop();
}