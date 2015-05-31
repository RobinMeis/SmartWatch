#ifndef OLED_H
#define OLED_H
void OLED_Init(void);
void OLED_Start(void);
void OLED_Stop(void);
void OLED_Write(uint8_t data);
void OLED_Command(uint8_t command);
#endif
