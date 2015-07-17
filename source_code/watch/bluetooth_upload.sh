echo Es sind root Rechte erforderlich!
sudo echo OK: Root Rechte erhalten!
rm program.o main.elf main.hex
avr-gcc -mmcu=atmega328p -Os -o program.o *.c libraries/*.c apps/*.c
avr-gcc program.o -o main.elf
avr-objcopy -O ihex -j .text -j .data main.elf main.hex
avr-size --mcu=atmega328p -C main.elf
sudo python3 ../tools/bluetooth_upload/upload.py main.hex
