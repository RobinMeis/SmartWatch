volatile unsigned char touch_byte=1, read=1;

void set_touch_byte(unsigned char new_byte) { //Parse from UART emulator
  if (read==1) {
    touch_byte = new_byte;
    read=0;
  }
}

unsigned char read_buttons(void) {
  if (read==0) {
    read=1;
    return touch_byte;
  }
  return 0;
}
