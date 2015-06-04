#include <avr/pgmspace.h>
#include "font.h"

void write_character(unsigned int character, unsigned char x, unsigned char y) {
  unsigned int end;
  unsigned char bit, byte; //TODO: Remove if y is specified in function

  if (character > 126)
    return;

  for (character=character*5, end = character + 5; character<end; ++character, ++x) {
    byte = pgm_read_byte(&font[character]);
    for (bit=0; bit<8; ++bit)
      if (byte& (1<<bit))
        OLED_set_pixel(x, y+bit, 1);
  }
}


void write_string(char* string, unsigned char space, unsigned char x, unsigned char y) {
  space += 5;
  for(;*string != 0x00; ++string, x+=space)
    write_character(*string, x, y);
}
