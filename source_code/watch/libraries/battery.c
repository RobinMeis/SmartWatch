#include <avr/io.h>

void battery_init(void) {
  ADMUX = (1<<REFS0);
  ADCSRA = (1<<ADPS1) | (1<<ADPS0);
  ADCSRA |= (1<<ADEN);

  ADCSRA |= (1<<ADSC);
  while (ADCSRA & (1<<ADSC) ) {}
  (void) ADCW;
}

unsigned char battery_get_bars (void) {
  ADMUX = (ADMUX & ~(0x1F)) | (1 & 0x1F);
  ADCSRA |= (1<<ADSC);
  while (ADCSRA & (1<<ADSC) ) {}
  uint16_t adc_value = ADCW;
  if (adc_value<=708) { //Shut down
    //TODO: Implement sleep
  } else if (adc_value<=752) //0 Bars
    return 0;
  else if (adc_value<=793) //1 Bar
    return 1;
  else if (adc_value<=833) //2 Bars
    return 2;
  else if (adc_value>833) //3 Bars
    return 3;
}
