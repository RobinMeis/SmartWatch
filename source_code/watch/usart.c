#define F_CPU 8000000UL
#define BAUD 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 16UL))) - 1)

#include <avr/io.h>

void usart_init(void) {
  UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
  UBRR0L = (uint8_t)(BAUD_PRESCALLER);
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01));
}

void usart_send_char(unsigned char data) {
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = data;
}

void usart_send_string(char* string) {
  for(;*string != 0x00; string++)
    usart_send_char(*string);
}

unsigned char usart_receive(void) {
  while(!(UCSR0A & (1<<RXC0)));
  return UDR0;
}
