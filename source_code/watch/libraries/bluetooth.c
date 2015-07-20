#define F_CPU 8000000UL //TODO: Set Global
#define UART_BAUD_RATE 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "ancs.h"

unsigned int c;
unsigned char command[15], ok=0, buffer_index=0;

void bluetooth_init(void) {
  DDRD &= ~(1<<2); //State pin
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
}

void bluetooth_reset(void) {
  PORTD|=(1<<2);
  OLED_clear();
  write_string("Verbindung", 1, 2, 49, 0);
  write_string("trennen", 1, 1, 0, 20);
  OLED_display();
  while ((PIND & (1<<2))) {}
  restore_bluetooth();
  OLED_clear();
  write_string("Update", 1, 2, 49, 0);
  write_string("abgeschlossen", 1, 1, 0, 20);
  OLED_display();
  _delay_ms(1000);
}

void buffer_reset() {
  buffer_index=0;
  ok=0; //TODO: GLOBAL VARIABLE!!!!!
  command[0]='\0';
}

unsigned char find_command(unsigned char *find, unsigned char matching, unsigned char length) {
  unsigned char i;
  for (i=0; i<matching; ++i)
    if (find[i]!=command[i])
      return 0;

  if (length == buffer_index)
    return 1;
  else
    return 0;
}

void parse_transmission() {
  c = uart_getc();
  if (!(c & UART_NO_DATA)) {
    if (c & UART_FRAME_ERROR || c & UART_OVERRUN_ERROR || c & UART_BUFFER_OVERFLOW) {
      //I know, program chrashes. TODO: Add error handling
    }
    if (c=='+')
      buffer_reset();
    else {
      if (buffer_index>13) buffer_index=0; //Prevent command buffer overflow

      command[buffer_index] = c;
      command[++buffer_index] = '\0';

      if (c=='O') ok=1; //Skip unsupported commands TODO: This does not work at the moment. Fix!
      else if (ok==1)
        if (c=='K') {
          buffer_reset();
        }

      if (!strcmp(command, "CONN")) {
        draw_bluetooth(0,0,1);
        OLED_display();
        buffer_reset();
      } else if (!strcmp(command, "LOST")) {
        draw_rectangle(0,0,7,10,0);
        OLED_display();
        buffer_reset();
        //TODO: Reset ANCS storage
      } else if (find_command("TIME:",5,11)) {
        char value[2];

        value[0] = command[5];
        value[1] = command[6];
        set_time_value(0, atoi(value));

        value[0] = command[7];
        value[1] = command[8];
        set_time_value(1, atoi(value));

        value[0] = command[9];
        value[1] = command[10];
        set_time_value(2, atoi(value));
        buffer_reset();
      } else if (find_command("DATE:",5,14)) {
        char value[4];

        value[0] = command[5];
        value[1] = command[6];
        set_time_value(3, atoi(value));

        value[0] = command[7];
        value[1] = command[8];
        set_time_value(4, atoi(value));

        value[0] = command[9];
        value[1] = command[10];
        value[2] = command[11];
        value[3] = command[12];
        set_year(atoi(value));
        buffer_reset();
      } else if (find_command("ANCS8",5,13)) {
        uart_puts("hi");

        ancs_parse(&command);
        buffer_reset();
      } else if (!strcmp(command, "UPDATE")) {
        update();
      } else {
        //uart_puts(command);
      }
    }
  }
}
