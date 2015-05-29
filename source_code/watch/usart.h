#ifndef USART_H
#define USART_H
void usart_init(void);
void usart_send_char(unsigned char data);
void usart_send_string(char* StringPtr);
unsigned char usart_receive(void);
#endif
