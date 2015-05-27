echo Es sind root Rechte erforderlich!
sudo echo OK: Root Rechte erhalten!
avr-gcc -mmcu=atmega328p -Os -c main.c -o main.o
avr-gcc main.o -o main.elf
avr-objcopy -O ihex -j .text -j .data main.elf main.hex
avr-size --mcu=atmega328p -C main.elf
sudo avrdude -c avrisp2 -p m328p -U flash:w:main.hex:a
