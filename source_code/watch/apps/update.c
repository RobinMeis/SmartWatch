#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>

void update(void) {
  OLED_clear();
  write_string("Update", 1, 2, 49, 0);
  write_string("Vorbereitung", 1, 1, 0, 20);
  OLED_display();

  uart_puts("AT");
  _delay_ms(500);
  uart_puts("AT+NOTI0");
  _delay_ms(500);
  uart_puts("AT");
  _delay_ms(500);
  uart_puts("AT+ANCS0");
  _delay_ms(500);
  uart_puts("AT");
  _delay_ms(500);
  uart_puts("AT+RESET");
  _delay_ms(500);
  OLED_clear();
  write_string("Update", 1, 1.5, 49, 0);
  write_string("Warte auf Verbindung", 1, 1, 0, 20);
  OLED_display();
  while (!(PIND & (1<<2))) {}
  OLED_clear();
  write_string("Update", 1, 1.5, 49, 0);
  write_string("Wird durchgeführt", 1, 1, 0, 20);
  OLED_display();
  void (*bootloader)( void ) = 0x3C00;
  bootloader();
}

void restore_bluetooth(void) {
  uart_puts("AT");
  _delay_ms(500);
  uart_puts("AT+NOTI1");
  _delay_ms(500);
  uart_puts("AT");
  _delay_ms(500);
  uart_puts("AT+ANCS1");
  _delay_ms(500);
  uart_puts("AT");
  _delay_ms(500);
  uart_puts("AT+RESET");
  _delay_ms(500);
}
