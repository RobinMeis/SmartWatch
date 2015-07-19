#define MAXSIZE 30000

#include "font.h"
#include <avr/pgmspace.h>

const unsigned short PROGMEM notification_symbols[176] = {
  0, 384, 2016, 3120, 6552, 15324, 15324, 31998, 32510, 16124, 16380, 7928, 4080, 2016, 384, 0, //other
  0, 24, 60, 62, 62, 30, 14, 14, 28, 56, 6264, 15600, 32736, 32704, 16128, 0, //(missed) call
  0, 0, 0, 0, 0, 6168, 9252, 16962, 16962, 9252, 8184, 0, 0, 0, 0, 0, //Voicemail
  1020, 1026, 1026, 1026, 1026, 1020, 28, 16280, 16464, 16448, 16448, 16448, 16256, 14336, 6144, 2048,  //Social
  0, 32766, 28686, 32766, 32766, 19114, 32766, 19114, 32766, 19114, 32766, 19114, 32766, 19114, 32766, 0, //Schedule
  0, 0, 0, 32766, 24582, 20490, 18450, 17442, 16962, 16770, 16386, 16386, 16386, 32766, 0, 0, //Email
  0, 0, 32766, 16386, 16386, 24570, 16386, 24314, 16634, 24314, 16634, 20218, 16386, 32766, 0, 0, //News
  0, 0, 7800, 16380, 32718, 32718, 30278, 28944, 16316, 8120, 4080, 2016, 960, 384, 0, 0, //health and fitness
  0, 2016, 8184, 16380, 14460, 30654, 32734, 32518, 32750, 32518, 32734, 14268, 14460, 8184, 2016, 0, //finance
  384, 2016, 4080, 3696, 7224, 7224, 3696, 4080, 4080, 2016, 2016, 960, 960, 384, 384, 0, //location
  0, 0, 0, 7224, 16380, 27630, 32710, 27630, 32766, 32766, 31806, 28686, 8196, 0, 0, 0,  //entertainment
};

const unsigned char PROGMEM bluetooth_symbol[5] = {12,20,37,22,12}; //symbol is mirrored at 5. value

void draw_vertical(unsigned char x, unsigned char y, unsigned char end, unsigned char state) { //x position, start y position, end y position, state of the pixel (on/off)
  for (; y<=end; ++y)
    OLED_set_pixel(x, y, state);
}

void draw_horizontal(unsigned char x, unsigned char y, unsigned char end, unsigned char state) { //y position, start x position, end x position, state of the pixel (on/off)
  for (; x<=end; ++x)
    OLED_set_pixel(x, y, state);
}

void draw_line(char x0, char y0, char x1, char y1, char state) { //Bresenham algorithm
  char dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
  char dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
  int err = dx+dy, e2;

  for(;;){
    OLED_set_pixel(x0, y0, state);
    if (x0==x1 && y0==y1) break;
    e2 = 2*err;
    if (e2 > dy) {err += dy; x0 += sx;}
    if (e2 < dx) {err += dx; y0 += sy;}
  }
}

void draw_circle(char x0, char y0, char radius, char state) {
  char f = 1 - radius;
  char ddF_x = 0;
  char ddF_y = -2 * radius;
  char x = 0;
  char y = radius;

  OLED_set_pixel(x0, y0 + radius, state);
  OLED_set_pixel(x0, y0 - radius, state);
  OLED_set_pixel(x0 + radius, y0, state);
  OLED_set_pixel(x0 - radius, y0, state);

  for(; x < y;) {
    if(f >= 0) {
      --y;
      ddF_y += 2;
      f += ddF_y;
    }
    ++x;
    ddF_x += 2;
    f += ddF_x + 1;

    OLED_set_pixel(x0 + x, y0 + y, state);
    OLED_set_pixel(x0 - x, y0 + y, state);
    OLED_set_pixel(x0 + x, y0 - y, state);
    OLED_set_pixel(x0 - x, y0 - y, state);
    OLED_set_pixel(x0 + y, y0 + x, state);
    OLED_set_pixel(x0 - y, y0 + x, state);
    OLED_set_pixel(x0 + y, y0 - x, state);
    OLED_set_pixel(x0 - y, y0 - x, state);
  }
}

void draw_rectangle(char x, char y, char width, char height, char state) {
  unsigned char yn;
  width+=x;
  height+=y;
  for (; x < width; ++x)
    for (yn=y; yn < height; ++yn)
      OLED_set_pixel(x, yn, state);
}

void draw_bluetooth(char x, char y, char state) { //TODO: Use progmen instead of RAM
  unsigned char i, n;

  for (i=0; i<5; ++i)
    for (n=0; n<6; ++n)
      if (pgm_read_byte(&bluetooth_symbol[i])& (1<<n))
        OLED_set_pixel(x+n, y+i, state);

  for (i=0; i<5; ++i)
    for (n=0; n<6; ++n)
      if (pgm_read_byte(&bluetooth_symbol[i])& (1<<n))
        OLED_set_pixel(x+n, y+9-i, state);
}

void draw_battery(char x, char y, char bars) {
  draw_horizontal(x, y, x+11, 1);
  draw_horizontal(x, y+7, x+11, 1);
  draw_vertical(x, y, y+7, 1);
  draw_vertical(x+11, y, y+7, 1);
  draw_rectangle(x+12,y+1,2,6,1);

  unsigned char n;
  for (n=0, x+=2, y+=2; n<bars; ++n, x+=3)//Draw filled bars
    draw_rectangle(x,y,2,4,1);

  for (; n<3; ++n, x+=3) //Remove eventually existing bars
    draw_rectangle(x,y,2,4,0);
}

void draw_notification_symbol(unsigned char category, unsigned char x_start, unsigned char y_start, unsigned char state) {
  //Notification symbols are 16x16 pixels
  unsigned char x,y;
  category*=16;
  for (y=0; y<16; ++y, ++category)
    for (x=0; x<16; ++x)
      if (pgm_read_word(&notification_symbols[category])& (1<<x))
        OLED_set_pixel(x+x_start, y+y_start, state);
}

void display_time(unsigned char *date, unsigned char x, unsigned char y) {
  unsigned char i, buffer[3];
  draw_rectangle(x,y,63,7,0);
  for (i=0; i<3; ++i) {

    if (date[i] < 10) {
      write_string("0 ", 1, 1, x, y);
      x+=7;
      itoa(date[i],buffer,10);
      write_string(buffer, 1, 1, x, y);
      x+=7;
    } else {
      itoa(date[i],buffer,10);
      write_string(buffer, 1, 1, x, y);
      x+=14;
    }

    if (i<2) {
      write_string(":", 1, 1, x, y);
      x+=7;
    }
  }
}
