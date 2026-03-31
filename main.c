//nothing

// New change 1 :)
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DPRT PORTD // LCD DATA PORT 
#define LCD_DDDR DDRD  // LCD DATA DDR 

#define LCD_CPRT PORTB // LCD CONTROL PORT 
#define LCD_CDDR DDRB  // LCD CONTOL DDR 

#define LCD_RS  0      // LCD RS  
#define LCD_RW  1      // LCD RW  
#define LCD_EN  2      // LCD EN


void initIO();
void blinkLED();
void lcdCommanda (unsigned char cmnd);
void lcdData(unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char x, unsigned char y);  
void lcd_print(unsigned char * str);


int main(void) {
	unsigned char prompt1[] = "It's almost";
	unsigned char prompt2[] = "spring break!";

	initIO();
	lcd_init();  
	lcd_gotoxy(1,1);  
	lcd_print(prompt1);  
	lcd_gotoxy(1,2);  
	lcd_print(prompt2);       
	while(1)
		blinkLED();    // Stay here forever  
	return 0; 
}   



/*********************************
 *********** FUNCTIONS ***********
 *********************************/
 
 void initIO() {
	DDRB =  (1 << PINB5);
	PORTB = (1 << PINB5);
}

void blinkLED() {
	PORTB ^= (1 << PINB5);
	_delay_ms(200);
}

//**************************************************************** 
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


 