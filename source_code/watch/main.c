//TODO: Do every TODO in every file!
//TODO: Check each header file for missing functions

#define F_CPU 8000000UL //TODO: Set Global
#define UART_BAUD_RATE 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "libraries/uart.h"
#include "libraries/oled.h"
#include "libraries/font.h"

int main(void){
  OLED_Init();
  OLED_display(); //Boot screen

  unsigned int c;
  unsigned char command[10], ok=0, index=0;
  //char buffer[7];
  //int  num=134;
  uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
  sei();

  _delay_ms(500);

  OLED_clear();
  OLED_display();

  //draw_circle(100,50,10,1);
  //write_string("Hobbits sind klein", 1, 1, 0, 30);
  //write_string("17:17", 1, 3, 10,60);
  //draw_rectangle(160,10,10,10,1);
  //OLED_clear();
  OLED_display();

  while (1) {
    c = uart_getc();
    if (!(c & UART_NO_DATA)) {
      if (c & UART_FRAME_ERROR || c & UART_OVERRUN_ERROR || c & UART_BUFFER_OVERFLOW) {}
        //return 0; //I know, program chrashes. TODO: Add error handling
      //uart_putc((unsigned char)c);

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
        //} else if (!strcmp(command, "LOS")) {
        } else if (command[0]=='L'&&command[1]=='O'&&command[2]=='S'&&command[3]=='T') {
          draw_rectangle(0,0,7,10,0);
          OLED_display();
          index=0;
        }
        uart_putc(c);
      }
    }
      /*if (c=='O') ok=1;
      else if (ok==1)
        if (c=='K') {
          command[index-2] = '\0';
          index=0;
          uart_puts(command);
          if (!strcmp(command, "CONN")) {
            draw_bluetooth(0,0,1);
            OLED_display();
          }
        } else ok=0;
      //if (command[0] == 'L' && command[1] == 'O' && command[2] == 'S' && command[3] == 'T') {
      if (!strcmp(command, "LOST")) {
        draw_rectangle(0,0,7,10,0);
        OLED_display();
      }*/
  }
  return 0;
}
