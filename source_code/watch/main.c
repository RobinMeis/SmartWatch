//TODO: Do every TODO in every file!
//TODO: Check each header file for missing functions
//TODO: Add description to libraries

#define F_CPU 8000000UL //TODO: Set Global

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "libraries/oled.h"
#include "libraries/font.h"
#include "libraries/battery.h"
#include "libraries/clock.h"
#include "libraries/bluetooth.h"
#include "libraries/update.h"
#include "libraries/app_controller.h"

int main(void){
  OLED_Init();
  OLED_display(); //Boot screen

  bluetooth_init();
  clock_init();
  bluetooth_init();
  battery_init();
  sei();

  //_delay_ms(1000);
  OLED_clear();

  draw_notification_symbol(0,0,10,1);
  draw_notification_symbol(1,15,10,1);
  draw_notification_symbol(2,31,10,1);
  draw_notification_symbol(3,47,10,1);
  draw_notification_symbol(4,63,10,1);
  draw_notification_symbol(5,79,10,1);
  draw_notification_symbol(6,95,10,1);
  draw_notification_symbol(7,111,10,1);
  draw_notification_symbol(8,0,30,1);
  draw_notification_symbol(9,15,30,1);
  draw_notification_symbol(10,31,30,1);

  OLED_display();

  while (1) {
    draw_battery(112,0,battery_get_bars());
    OLED_display();
    OLED_clear();
    parse_transmission();
    display_time(32, 0);
    display_date(0, 30);
  }
  return 0;
}
