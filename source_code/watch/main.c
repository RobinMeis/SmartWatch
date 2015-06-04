//TODO: Do every TODO in every file!

#define F_CPU 8000000UL //TODO: Set Global

#include <avr/io.h>
#include <util/delay.h>

#include "libraries/usart.h"
#include "libraries/oled.h"
#include "libraries/font.h"

int main(void){
  usart_init();
  usart_send_string("ready\n");

  OLED_Init();
  OLED_display(); //Boot screen
  _delay_ms(500);
  OLED_clear();
  OLED_display();

  draw_horizontal(10, 10, 30, 1);
  draw_vertical(10,10,30,1);
  draw_line(0,20,100,40,1);
  draw_circle(100,50,10,1);
  write_string("Hobbits sind klein", 1, 0, 30);
  OLED_display();

  usart_send_string("done\n");
  while (1) {
  }
  return 0;
}
