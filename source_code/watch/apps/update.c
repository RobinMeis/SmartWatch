#define F_CPU 8000000UL
//TODO: Move to libraries
#include <util/delay.h>
#include <avr/io.h>

void update(void) {
  uart_puts("UPDATEWAIT");
  OLED_clear();
  write_string("Verbindung", 1, 2, 49, 0);
  write_string("trennen", 1, 1, 0, 20);
  OLED_display();
  while ((PIND & (1<<2))) {}
  OLED_clear();
  write_string("Vorbereitung", 1, 2, 49, 0);
  OLED_display();
  uart_puts("AT+NOTI0");
  _delay_ms(500);
  uart_puts("AT+ANCS0");
  _delay_ms(500);
  uart_puts("AT+RESET");
  _delay_ms(500);
  OLED_clear();
  write_string("Update", 1, 1.5, 49, 0);
  write_string("Verbinden!", 1, 1, 0, 20);
  OLED_display();
  while (!(PIND & (1<<2))) {}
  OLED_clear();
  write_string("Update", 1, 1.5, 49, 0);
  write_string("Wird durchgeführt", 1, 1, 0, 20);
  OLED_display();
  void (*bootloader)( void ) = 0x3C00;
  _delay_ms(500);
  bootloader();
}

void restore_bluetooth(void) {
  uart_puts("AT+NOTI1");
  _delay_ms(500);
  uart_puts("AT+ANCS1");
  _delay_ms(500);
  uart_puts("AT+RESET");
  _delay_ms(500);
}
