echo Es sind root Rechte erforderlich!
sudo echo OK: Root Rechte erhalten!
rm program.o main.elf main.hex
avr-gcc -Wl,--section-start=.text=7800 -Wl,-Map=test.map -mmcu=atmega328p -Os -o program.o *.c libraries/*.c -lm  -o main.elf
#avr-gcc program.o -o main.elf
avr-objcopy -O ihex -j .text -j .data main.elf main.hex
avr-size --mcu=atmega328p -C main.elf
sudo avrdude -c avrisp2 -p m328p -U flash:w:main.hex:a
