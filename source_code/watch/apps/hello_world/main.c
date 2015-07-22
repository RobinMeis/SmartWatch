#include "../../libraries/touch.h"

void hello_world(void) {
  char buffer[20];

  while (1) {
    OLED_clear();
    draw_headline();
    write_string("Hello World",1,1,0,20);
    system_functions();


    if (read_buttons()==66) {
      OLED_clear();
      write_string("leave app",1,1,0,0);
      OLED_display();
      return;
    }
    OLED_display();
  }
}
