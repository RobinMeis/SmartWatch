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
  unsigned char i, n, symbol[5] = {12,20,37,22,12}; //symbol is mirrored at 5. value

  for (i=0; i<5; ++i)
    for (n=0; n<6; ++n)
      if (symbol[i]& (1<<n))
        OLED_set_pixel(x+n, y+i, state);

  for (i=0; i<5; ++i)
    for (n=0; n<6; ++n)
      if (symbol[i]& (1<<n))
        OLED_set_pixel(x+n, y+9-i, state);
}

void draw_battery(char x, char y, char state, char filled) {
  draw_horizontal(x, y, x+11, 1);
  draw_horizontal(x, y+7, x+11, 1);
  draw_vertical(x, y, y+7, 1);
  draw_vertical(x+11, y, y+7, 1);
  draw_rectangle(x+12,y+1,2,6,1);

  unsigned char n;
  for (n=0, x+=2, y+=2; n<filled; ++n, x+=3) {
    draw_rectangle(x,y,2,4,1);
  }

}
