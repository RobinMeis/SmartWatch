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

  DDRB = 63; //Touch buttons
  unsigned char port_b;

  battery_init();

  _delay_ms(1000);
  OLED_clear();
  write_string("22:10", 1, 1, 49, 0);
  OLED_display();

  while (1) {
    draw_battery(112,0,battery_get_bars());
    OLED_display();

    DDRB |= 63;//PB1 -> output
    PORTB &= ~63;  //PB1 low -> sensor entladen
    DDRB &= ~63; //PB1 -> input
    PORTB |= 63;   //Sensor über internen Pull up laden
    asm volatile("nop"); //wait 7CK = 0,4375µs @ 16MHz -> anpassen an Sensorfläche
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");


    port_b = PINB;
    //Kapazität(Spannung am Sensor überprüfen
    if(!(port_b & (1<<0)))
      uart_puts("Button 0\n");
    if(!(port_b & (1<<1)))
      uart_puts("Button 1\n");
    if(!(port_b & (1<<2)))
      uart_puts("Button 2\n");
    if(!(port_b & (1<<3)))
      uart_puts("Button 3\n");
    if(!(port_b & (1<<4)))
      uart_puts("Button 4\n");
    if(!(port_b & (1<<5)))
      uart_puts("Button 5\n");

    _delay_ms(25);
    DDRB |= 63;//PB1 als output
    PORTB &= ~63;  //PB1 auf Masse -> Sensor entladen
    _delay_ms(10);

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
