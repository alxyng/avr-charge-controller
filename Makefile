# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
F_CPU = 4000000UL

CC = avr-gcc
CFLAGS = -g -mmcu=atmega8 -Wall -Os

OUTSIZE = avr-size
OBJ2HEX = avr-objcopy

BUILDDIR=build

SOURCES=$(wildcard *.c)

OBJS=$(SOURCES:.c=.o)
OBJDIR=build

ISP = avrispmkII

main.hex: main.out
	$(OUTSIZE) main.out
	$(OBJ2HEX) -R .eeprom -O ihex main.out main.hex

main.out: main.o adc.o led.o uart.o
	avr-gcc -g -mmcu=atmega8 -o main.out -Wl,-u,vfprintf -lprintf_flt -lm -Wl,-Map,main.map main.o adc.o led.o uart.o

main.o: main.c
	avr-gcc -g -mmcu=atmega8 -Wall -Os -c main.c

adc.o: adc.c adc.h
	avr-gcc -g -mmcu=atmega8 -Wall -Os -c adc.c

led.o: led.c led.h
	avr-gcc -g -mmcu=atmega8 -Wall -Os -c led.c

uart.o: uart.c uart.h
	avr-gcc -g -mmcu=atmega8 -Wall -Os -c uart.c

#%.obj : %.o $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $@

#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@

# Utils

# enable brown out detection at 2.7v and use 8MHz internal RC oscillator
fuses:
	avrdude -c $(ISP) -p m8 -U lfuse:w:0xA4:m -U hfuse:w:0xD9:m

fuses2:
	avrdude -c $(ISP) -p m8 -U lfuse:w:0xAE:m -U hfuse:w:0xD9:m

# default fuses
fusesdefault:
	avrdude -c $(ISP) -p m8 -U lfuse:w:0xE1:m -U hfuse:w:0xD9:m

# erase
erase:
	avrdude -c $(ISP) -p m8 -e

load: main.hex
	avrdude -c $(ISP) -p m8 -e -U flash:w:main.hex

# Don't verify
loadn: main.hex
	avrdude -c $(ISP) -p m8 -e -V -U flash:w:main.hex

clean:
	rm *.o *.out *.map *.hex
