#include "clock.h"

#include <avr/io.h>
#include <avr/interrupt.h>


volatile unsigned char date[5] = {23,59,59,28,2}; // hour, minute, seconds, day, month, i know, unix timestamp could have benn used here but is completely nonsense in this case
volatile unsigned short year = 2015; //TODO: Change to birthdate of first watch!

unsigned char days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //TODO Store in flash only!

ISR (TIMER1_COMPA_vect) {
  if (date[2] == 59) { //Second
    date[2] = 0;
    if (date[1] == 59) { //Minute
      date[1] = 0;
      if (date[0] == 23) { //Hour
        date[0] = 0;

        if (date[3]==28 && date[4]==2 && year%4==0 && year%100) //Leap year?
          ++date[3];
        else if (date[3]==28 && date[4]==2 && year%400==0)
          ++date[3];
        else {
          if (date[3] >= days[date[4]-1]) { //Day
            date[3] = 1;
            if (date[4]==12) { //Month/year
              date[4]=1;
              ++year;
            } else
              ++date[4];
          } else
            ++date[3];
        }
      }
      else
        ++date[0];
    } else
      ++date[1];
  } else
    ++date[2];
}

void clock_init() {
  OCR1A = 7812;
	TCCR1B = (1<<CS12)|(1<<CS10)|(1<<WGM12);
	TIMSK1 |= (1<<OCIE1A);
}

void display_time(unsigned char x, unsigned char y) {
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

void display_date(unsigned char x, unsigned char y) {
  unsigned char i, buffer[5];
  for (i=3; i<5; ++i) {
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
    write_string(".", 1, 1, x, y);
    x+=7;
  }
  itoa(year,buffer,10);
  write_string(buffer, 1, 1, x, y);
}
