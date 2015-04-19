# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#F_CPU = 1000000UL

main.hex: main.out
	avr-size main.out
	avr-objcopy -R .eeprom -O ihex main.out main.hex

main.out: main.o uart.o
	avr-gcc -g -mmcu=atmega8 -o main.out -Wl,-u,vfprintf -lprintf_flt -lm -Wl,-Map,main.map main.o uart.o

main.o: main.c
	avr-gcc -g -mmcu=atmega8 -Wall -Os -c main.c

uart.o: uart.c
	avr-gcc -g -mmcu=atmega8 -Wall -Os -c uart.c

# Utils

# enable brown out detection at 2.7v and use 8MHz internal RC oscillator
fuses:
	avrdude -c avrispmkII -p m8 -U lfuse:w:0xA4:m -U hfuse:w:0xD9:m

# default fuses
fusesdefault:
	avrdude -c avrispmkII -p m8 -U lfuse:w:0xE1:m -U hfuse:w:0xD9:m

# erase
erase:
	avrdude -c avrispmkII -p m8 -e

load: main.hex
	avrdude -c avrispmkII -p m8 -e -U flash:w:main.hex

clean:
	rm *.o *.out *.map *.hex
