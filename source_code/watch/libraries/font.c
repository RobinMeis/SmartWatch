#include <avr/pgmspace.h>
#include "font.h"

//TODO: correct parameters of functions in header!
//TODO: CHECK indention in all files

void write_character(unsigned int character, unsigned char size, unsigned char x, unsigned char y) {
  unsigned int end;
  unsigned char bit, byte;

  if (character > 126)
    return;

  if (size==1) { //saves time TODO: klammern erforderlich? check in all files!
    for (character=character*5, end = character + 5; character<end; ++character, ++x) {
      byte = pgm_read_byte(&font[character]);
      for (bit=0; bit<8; ++bit)
        if (byte& (1<<bit))
          OLED_set_pixel(x, y+bit, 1);
    }
  } else {
    for (character=character*5, end = character + 5; character<end; ++character, x+=size) {
      byte = pgm_read_byte(&font[character]);
      for (bit=0, y=0; bit<8; ++bit, y+=size)
        if (byte& (1<<bit))
          //OLED_set_pixel(x, y+bit, 1);
          draw_rectangle(x,y,size,size, 1);
    }
  }
}


void write_string(char* string, unsigned char space, unsigned char size, unsigned char x, unsigned char y) {
  space += 5*size + space*size;
  for(;*string != 0x00; ++string, x+=space)
    write_character(*string, size, x, y);
}
