#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "i2cmaster.h" //Thanks to Peter Fleury for his I2C library (http://homepage.hispeed.ch/peterfleury/index.html)

void OLED_Start(void) { //Basically an I2C layer
  i2c_start_wait(0x78+I2C_WRITE); //0x78 is the I2C address of OLED display
}

void OLED_Stop(void) {
  i2c_stop();
}

void OLED_Write(uint8_t data) {
  i2c_write(data);
}

void OLED_Command(uint8_t command) { //Function for sending a normal command
  OLED_Start();
  OLED_Write(0x00);
  OLED_Write(command);
  OLED_Stop();
}

void OLED_Init(void) {
  DDRC |= (1<<4); //Reset of OLED
  PORTC |= (1<<4);
  _delay_ms(1);
  PORTC &= ~(1<<4);
  _delay_ms(10);
  PORTC |= (1<<4);

  i2c_init(); //Initialization for the I2C Bus

  OLED_Command(0xAE); //Initialization sequenze for OLED
  OLED_Command(0xD5);
  OLED_Command(0x80);
  OLED_Command(0xA8);
  OLED_Command(0x3F);
  OLED_Command(0xD3);
  OLED_Command(0x0);
  OLED_Command(0x40 | 0x0); //TODO: Startline möglicherweise zu ändern
  OLED_Command(0x8D);
  OLED_Command(0x14); //VCC
  OLED_Command(0x20);
  OLED_Command(0x00);
  OLED_Command(0xA0 | 0x1);
  OLED_Command(0xC8);
  OLED_Command(0xDA);
  OLED_Command(0x12);
  OLED_Command(0x81);
  OLED_Command(0xCF); //VCC
  OLED_Command(0xD9);
  OLED_Command(0xF1);
  OLED_Command(0xDB);
  OLED_Command(0x40);
  OLED_Command(0xA4);
  OLED_Command(0xA6);
  OLED_Command(0xAF); //Switch on
}
