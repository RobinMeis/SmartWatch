//TODO: Läuft Takt auf externen 8MHz? (Fuses)

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main (void) {

   DDRB |= (1 << PB5);

   while(1) {
       PORTB ^= (1 << PB5);
       _delay_ms(1000);
   }

   return 0;
}
