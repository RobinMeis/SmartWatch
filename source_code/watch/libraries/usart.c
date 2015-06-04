#define F_CPU 8000000UL
#define BAUD 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 16UL))) - 1)
#define BUFFER_SIZE 20

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char buffer[BUFFER_SIZE], buffer_index=0;

void usart_init(void) {
  UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
  UBRR0L = (uint8_t)(BAUD_PRESCALLER);
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01));

  UCSR0B |= (1<<RXEN0)|(1<<RXCIE0);
}

ISR(USART_RX_vect) { //Receive interrupt
  unsigned char data=UDR0;
  ++buffer_index;
  if (buffer_index==BUFFER_SIZE||data=='+') {
    UCSR0B &= ~((1<<RXEN0)|(1<<RXCIE0)); //Switch to transmission interruot
    UCSR0B |= (1<<TXEN0)|(1<<UDRIE0);
    return;
  }
  buffer[buffer_index] = data;
}

ISR(USART_UDRE_vect) { //Transmission interrupt
  UDR0=buffer[buffer_index];
  --buffer_index;
  if (buffer_index==0) {
    UCSR0B &= ~((1<<TXEN0)|(1<<UDRIE0)); //Switch to receive interrupt
    UCSR0B |= (1<<RXEN0)|(1<<RXCIE0);
  }
}

void parse_buffer(void) {

}

/*void usart_send_char(unsigned char data) { //Not required anymore since UART is now based on interrupts TODO: Remove when interrupt tested
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = data;
}

void usart_send_string(char* string) {
  for(;*string != 0x00; ++string)
    usart_send_char(*string);
}

unsigned char usart_receive(void) {
  while(!(UCSR0A & (1<<RXC0)));
  return UDR0;
}*/
