#ifndef GRAPHICS_H
#define GRAPHICS_H
void draw_horizontal(unsigned char x, unsigned char y, unsigned char end, unsigned char state);
void draw_vertical(unsigned char y, unsigned char x, unsigned char end, unsigned char state);
void draw_line(char x0, char y0, char x1, char y1);
void draw_circle(int x0, int y0, int radius, char state); //TODO: Datentypen anpassen!
void draw_rectangle(char x, char y, char width, char height, char state);
#endif
