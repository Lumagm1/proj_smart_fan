#include "func.h"
#include <avr/io.h>

#define START       0x08
#define REPEATED_START  0x10
#define MT_SLA_ACK  0x18
#define MT_SLA_NACK 0x20
#define MT_DATA_ACK  0x28
#define MT_DATA_NACK 0x30
#define Arbitration_Lost 0x38
#define MR_SLA_ACK  0x40
#define MR_SLA_NACK 0x48
#define MR_DATA_ACK  0x50
#define MR_DATA_NACK 0x58


void ERROR(){
    // Handle error (e.g., blink an LED, send a message, etc.)
    while(1); // Infinite loop to indicate error
}

void i2c_init(){
    TWCR0 = (1<<TWEN);
}

void i2c_start(){
    TWCR0 = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR0 & (1<<TWINT)));

    if (((TWSR0 & 0xF8) != START) && ((TWSR0 & 0xF8) != REPEATED_START))
        ERROR();
}

void i2c_write(unsigned char data){
    TWDR0 = data;
    TWCR0 = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR0 & (1<<TWINT)));
    if ((TWSR0 & 0xF8) != MT_DATA_ACK) ERROR();
}

unsigned char i2c_read_ack(){
    TWCR0 = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR0 & (1<<TWINT)));
    return TWDR0;
}

unsigned char i2c_read_nack(){
    TWCR0 = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR0 & (1<<TWINT)));
    return TWDR0;
}
void i2c_stop(){
    TWCR0 = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void i2c(unsigned char data, unsigned char address){
    i2c_init();
    i2c_start();
    i2c_write(address); // Write address
    i2c_write(data); // Write data
    i2c_stop();
}