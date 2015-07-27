#define ANCS_CACHE_SIZE 50
#define ANCS_CATEGORIES 12

#define F_CPU 8000000UL
#include <util/delay.h>

unsigned char uuids[ANCS_CACHE_SIZE][4], buffer_index;
unsigned char category_id[ANCS_CACHE_SIZE], category_count[ANCS_CATEGORIES], ancs_index=0;

unsigned char find_matching(unsigned char *find, unsigned char *buffer, unsigned char matching, unsigned char length) {
  unsigned char i;
  for (i=0; i<matching; ++i)
    if (find[i]!=buffer[i])
      return 0;

  if (length == buffer_index)
    return 1;
  else
    return 0;
}

unsigned char hex_to_int(unsigned char *string, unsigned char length) { //TODO: improve!
  unsigned char decimal=0, i;
  unsigned char hex[15]="123456789ABCDEF"; //TODO: USE PROGMEM
  --length;
  for (i=0;i<15;++i)
    if (string[length]==hex[i]) {
      decimal = i + 1;
      break;
    }

  for (i=0;i<15&&length==1;++i)
    if (string[0]==hex[i]) {
      decimal += (i + 1)*16;
      break;
    }
}

void ancs_init(void) {
  unsigned char i;
  for (i=0; i<ANCS_CATEGORIES; ++i)
    category_count[i] = 0;

    for (i=0; i<ANCS_CACHE_SIZE; ++i)
      category_id[i] = 255;
}

const char *ancs_request_title(unsigned char *uuid) {
  unsigned char ancs_request[17] = "AT+ANCSUUID116", c, timeout;
  ancs_request[7] = uuid[0];
  ancs_request[8] = uuid[1];
  ancs_request[9] = uuid[2];
  ancs_request[10] = uuid[3];
  uart_puts(ancs_request); //Send command through UART
  ancs_request[0]='\0'; //Reuse to receive title

  OLED_clear();
  OLED_display();

  for(buffer_index=0;;) {
    c = uart_getc();
    if (c != 0) {
      if (buffer_index>=17 || c=='+') {
        ancs_request[0]='\0';
        buffer_index=0;
      } else {
        ancs_request[buffer_index]=c;
        ancs_request[++buffer_index]=c;
        if (find_matching("ANCS:",ancs_request,5,8))
          break;
      }
    }
  }

  for(;;)
    if (c = uart_getc() >= 0x20)
      break;

  ancs_request[0]='\0'; //Reuse to receive title
  for (buffer_index=0, timeout=0;timeout<20 && buffer_index<16;c = uart_getc())
    if (c == 0) {
        ++timeout;
        _delay_ms(1);
    } else if (c < 32);
    else {
      timeout=0;
      ancs_request[buffer_index] = c;
      ancs_request[++buffer_index] = '\0';
    }
  write_string("Anruf von:",1,1,0,0);
  write_string(ancs_request,1,1,0,30);
  uart_puts(ancs_request);
  return "ttile";
}

void ancs_parse(unsigned char *string) {
  unsigned char buffer[3], this_category_id;
  this_category_id = hex_to_int(&string[6],1); //Category ID

  buffer[0] = string[7]; buffer[1] = string[8]; //Category Count
  category_count[this_category_id] = hex_to_int(&buffer[0], 2);

  if (string[5] == '0') { //Added
    if (++ancs_index >= ANCS_CACHE_SIZE)
      ancs_index = 0;
    uuids[ancs_index][0] = string[9];
    uuids[ancs_index][1] = string[10];
    uuids[ancs_index][2] = string[11];
    uuids[ancs_index][3] = string[12];
    category_id[ancs_index] = this_category_id;

    if (string[6]=='1') { //Incoming call?
      OLED_clear();
      _delay_ms(200); //Wait for ANCS to get ready again
      ancs_request_title(uuids[ancs_index]);
      OLED_display();

      while (1) {}
    }
  } else if (string[5] == '1') { //Modified
    //TODO: What should happen here? Category count is already handled!
  } else if (string[5] == '2') { //Removed
    unsigned char i;
    for (i=0; i<ANCS_CACHE_SIZE; ++i)
      if (uuids[i][3] == string[12] && uuids[i][2] == string[11] && uuids[i][1] == string[10] && uuids[i][0] == string[9]) {
        category_id[i] = 255;
        i=ANCS_CACHE_SIZE;
      }
  }
  uart_puts(uuids[ancs_index]);
}
