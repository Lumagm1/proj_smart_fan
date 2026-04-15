#define F_CPU 16000000UL
#include "func.h"
#include <avr/io.h>
#include <util/delay.h>

#define LCD_ADDR 0x27 // I2C address of the LCD

void lcdCommanda (unsigned char cmnd) {  // LCD modes
	lcd_send(cmnd, 0); // Send command with RS = 0
}
void lcdData(unsigned char data) {  // LCD characters
	lcd_send(data, LCD_RS); // Send data with RS = 1
} 

void lcd_init() {  
	i2c_init();    // Initialize I2C communication
	_delay_ms(50);   // wait for LCD power-up
	
    // Force LCD into 4-bit mode using raw upper nibbles
    lcd_write4bits((0x30 | LCD_BL));   // 0011xxxx
    _delay_ms(5);

    lcd_write4bits((0x30 | LCD_BL) );   // 0011xxxx
    _delay_ms(1);

    lcd_write4bits((0x30 | LCD_BL) );   // 0011xxxx
    _delay_ms(1);

    lcd_write4bits((0x20 | LCD_BL) );   // 0010xxxx -> switch to 4-bit mode
    _delay_ms(1);

	lcdCommanda(0x28);				// Initialize LCD 2 line, 5x7 characters 
	 _delay_us(50);
	lcdCommanda(0x08);				// Display off, cursor off, blink off
	 _delay_us(50);
	lcdCommanda(0x01);				// Clear LCD  
	_delay_ms(2);					// Wait  
	lcdCommanda(0x06);				// Shift cursor right after display char.
	 _delay_us(50);
	lcdCommanda(0x0C);				// Display on, cursor on, blink on
	 _delay_us(50);
} 
 
void lcd_gotoxy(unsigned char x, unsigned char y) {  // Set cursor position, x is column (1-16), y is row (1-4)
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

void lcd_clear() {  
	lcdCommanda(0x01); // Clear display command
	_delay_ms(2); // Wait for the command to execute
}

//I2C LCD Communication Functions, these are used to send commands and data to the LCD via I2C
void lcd_expander_write(int data) { // This function writes a byte to the LCD via I2C
	i2c_start();
	i2c_address((LCD_ADDR << 1) | 0); // Write address
	i2c_data(data); // Write data
	i2c_stop();
}

void pulse_enable(int data) // essentially enable low -> enable high -> enable low, this is used to latch the data into the LCD
{
	lcd_expander_write(data & ~LCD_EN); // EN = 0, data lines set
	_delay_us(1);
	lcd_expander_write(data | LCD_EN);  // EN = 1 (latch data)
	_delay_us(1);                       // EN high pulse width >= 450ns
	lcd_expander_write(data & ~LCD_EN); // EN = 0
	_delay_us(50);                      // Wait for LCD to execute command
}

void lcd_write4bits(int data)
{
	pulse_enable(data); // Pulse the enable pin
}

void lcd_send(int value, int rs)
{
	lcd_write4bits(((value & 0xF0) | LCD_BL | rs) & ~LCD_RW); 		// Send upper bits in the 4-bit mode
	_delay_ms(1);
	lcd_write4bits((((value & 0x0F) << 4) | LCD_BL | rs) & ~LCD_RW);	// Send lower bits in the 4-bit mode, the i2c chip will combine the upper and lower bits to form the full command or data byte
	_delay_us(50);
}