//TODO: Do every TODO in every file!

#define F_CPU 8000000UL //TODO: Set Global

#include <avr/io.h>
#include <util/delay.h>

#include "libraries/usart.h"
#include "libraries/oled.h"

int main(void){
  usart_init();
  usart_send_string("ready\n");

  OLED_Init();
  OLED_display();
  OLED_clear();
  OLED_set_pixel(0,0,1);
  OLED_set_pixel(1,1,1);
  OLED_set_pixel(2,2,1);
  OLED_set_pixel(3,3,1);
  OLED_set_pixel(4,4,1);
  OLED_set_pixel(5,5,1);
  OLED_set_pixel(6,6,1);
  OLED_set_pixel(7,7,1);

  OLED_display();

  usart_send_string("done\n");
  while (1) {

  }
  return 0;
}
