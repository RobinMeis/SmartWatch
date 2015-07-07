//TODO: Do every TODO in every file!
//TODO: Check each header file for missing functions
//TODO: Add description to libraries

#define F_CPU 8000000UL //TODO: Set Global
#define UART_BAUD_RATE 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "libraries/uart.h" //Libraries
#include "libraries/oled.h"
#include "libraries/font.h"
#include "libraries/battery.h"
//#include "libraries/ancs.h"

#include "apps/update.h"

int main(void){
  OLED_Init();
  OLED_display(); //Boot screen

  unsigned int c;
  unsigned char command[14], ok=0, index=0;
  uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
  sei();

  DDRD &= ~(1<<2); //Bluetooth state
  PORTD|=(1<<2);
  restore_bluetooth();

  battery_init();

  _delay_ms(1000);
  OLED_clear();
  write_string("22:10", 1, 1, 49, 0);
  OLED_display();

  while (1) {
    draw_battery(112,0,battery_get_bars());
    OLED_display();

    c = uart_getc();
    if (!(c & UART_NO_DATA)) {
      if (c & UART_FRAME_ERROR || c & UART_OVERRUN_ERROR || c & UART_BUFFER_OVERFLOW) {
        //I know, program chrashes. TODO: Add error handling
      }
      if (c!='+') {
        if (index>8) index=0; //Prevent command buffer overflow

        command[index] = c;
        command[++index] = '\0';

        if (c=='O') ok=1; //Skip unsupported commands
        else if (ok==1)
          if (c=='K') {
            index=0;
            ok=0;
            command[0]='\0';
          }

        if (!strcmp(command, "CONN")) {
          draw_bluetooth(0,0,1);
          OLED_display();
          index=0;
        } else if (!strcmp(command, "LOST")) {
          draw_rectangle(0,0,7,10,0);
          OLED_display();
          index=0;
        } else if (!strncmp(command, "ANCS", 4)) {
          //uart_puts(command);
        } else if (!strcmp(command, "UPDATE")) {
          update();
        } else {
          uart_puts(command);
        }
      }
    }
  }
  return 0;
}
