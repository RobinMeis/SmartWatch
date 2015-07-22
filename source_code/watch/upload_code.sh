echo Es sind root Rechte erforderlich!
sudo echo OK: Root Rechte erhalten!
rm program.o main.elf main.hex
avr-gcc -mmcu=atmega328p -Os -o main.elf *.c libraries/*.c apps/*/*.c
avr-objcopy -O ihex -j .text -j .data main.elf main.hex
avr-size --mcu=atmega328p -C main.elf
sudo avrdude -B 1 -c avrisp2 -p m328p -U flash:w:main.hex:a
