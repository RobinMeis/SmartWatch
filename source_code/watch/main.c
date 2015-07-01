//TODO: Do every TODO in every file!
//TODO: Check each header file for missing functions
//TODO: Add description to libraries

#define F_CPU 8000000UL //TODO: Set Global
#define UART_BAUD_RATE 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "libraries/uart.h"
#include "libraries/oled.h"
#include "libraries/font.h"
//#include "libraries/ancs.h"


int main(void){
  OLED_Init();
  OLED_display(); //Boot screen

  unsigned int c;
  unsigned char command[14], ok=0, index=0;
  //char buffer[7];
  //int  num=134;
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
  sei();

  _delay_ms(250);
  OLED_clear();
  write_string("22:10", 1, 1, 49, 0);
  draw_battery(112,0,1,3);
  OLED_display();

  uart_puts("Hey there, I'm ready!");
  while (1) {
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
        uart_puts("Processing");
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
        } else {
          uart_puts(command);
        }
      }
    }
  }
  return 0;
}
