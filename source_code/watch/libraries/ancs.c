#define ANCS_CACHE_SIZE 50
#define ANCS_CATEGORIES 12

unsigned char uuids[ANCS_CACHE_SIZE][4];
unsigned char category_id[ANCS_CACHE_SIZE], category_count[ANCS_CATEGORIES], ancs_index=0;

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
