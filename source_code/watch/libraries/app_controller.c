#include <avr/pgmspace.h>
#include "../apps/hello_world/main.h"
#include "../apps/pong/main.h"
#include "../apps/messages/main.h"


typedef void (*function) (void);
const function apps[3] PROGMEM = {pong, messages, hello_world, };
const unsigned char name[3][16] = {"Pong","Nachrichten","Hello World"}; //TODO: Use progmem

void system_functions(void) {
  parse_transmission();
  //TODO: Battery check
  //TODO: Add crash check by using interrupt
}

unsigned char app_menu(void) { //Select app
  OLED_clear();

  unsigned char position = 1, buttons, n;
  write_string(&name[0],1,1,0,23);
  write_string(&name[1],1,1,10,33);
  write_string(&name[2],1,1,0,43);

  while (1) {
    draw_headline();
    OLED_display();
    system_functions();
    buttons = read_buttons();
    if (buttons==8) { //scroll up TODO: Switch Case TODO: Scrollen oder tippen?
      if (position>0) {
        n=--position;
        OLED_clear();
        if (position>0) write_string(&name[n-1],1,1,0,23);
        write_string(&name[n],1,1,10,33);
        write_string(&name[n+1],1,1,0,43);
      }
    } else if (buttons==16) { //scroll up
      if (position<2) {
        n=++position;
        OLED_clear();
        write_string(&name[n-1],1,1,0,23);
        write_string(&name[n],1,1,10,33);
        if (position<2) write_string(&name[n+1],1,1,0,43);
      }
    } else if (buttons==68)
      return position;
  }
}

void app_controller(void) {
  while(1) { //Never leave the app controller!
    function app = (function)pgm_read_word (&apps[app_menu()]);
    app();
  }
}
