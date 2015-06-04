#include <avr/pgmspace.h>
#include "font.h"

void write_character(unsigned int character, unsigned char x) {
  unsigned int end;

  if (character < 32 || character > 126)
    return;

  for (character=character*5, end = character + 5; character<end; ++character, ++x) {
    OLED_set_buffer(x, pgm_read_byte(&font[character]));
  }
}


void write_string(char* string, unsigned char space, unsigned char x) {
  space += 5;
  for(;*string != 0x00; ++string, x+=space)
    write_character(*string, x);
}
