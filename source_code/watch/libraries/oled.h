#ifndef OLED_H
#define OLED_H
void OLED_Init(void);
void OLED_Start(void);
void OLED_Stop(void);
void OLED_Write(unsigned char data);
void OLED_Command(unsigned char command);
void OLED_on(void);
void OLED_off(void);
void OLED_set_pixel(unsigned char x, unsigned char y, char state);
void OLED_display(void);
void OLED_clear(void);
void OLED_set_buffer(unsigned int index, unsigned char value);
#endif
