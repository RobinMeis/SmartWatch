//TODO: Läuft Takt auf externen 8MHz? (Fuses)
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"


int main(void){
  DDRB |= (1<<5); //Debug LED
  usart_init();


  while (1) {
    PORTB ^= (1<<5);
    usart_send_char(usart_receive()); //Sends received data back to computer
  }
  return 0;
}
