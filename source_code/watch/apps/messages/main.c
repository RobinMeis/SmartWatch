#include "../../libraries/touch.h"

void messages(void) {
  while (1) {
    OLED_clear();
    draw_headline();
    write_string("Nachrichten",1,1,0,20);
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
