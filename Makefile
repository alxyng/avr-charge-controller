# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
F_CPU = 4000000UL

CC = avr-gcc
CFLAGS = -std=c99 -g -mmcu=atmega8 -Wall -Os

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

main.out: main.o adc.o uart.o util.o
	avr-gcc -std=c99 -g -mmcu=atmega8 -Os -o main.out -lm -Wl,-Map,main.map main.o adc.o uart.o util.o

main.o: main.c util.h led.h
	avr-gcc $(CFLAGS) -c main.c

adc.o: adc.c adc.h
	avr-gcc $(CFLAGS) -c adc.c

uart.o: uart.c uart.h
	avr-gcc $(CFLAGS) -c uart.c

util.o: util.c util.h
	avr-gcc $(CFLAGS) -c util.c

#%.obj : %.o $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $@

#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@

# Utils

# DEFAULT - No brown out detection and use 1MHz internal RC oscillator
fuses_default:
	avrdude -c $(ISP) -p m8 -U lfuse:w:0xE1:m -U hfuse:w:0xD9:m

# Enable brown out detection at 2.7v and use 1MHz internal RC oscillator
fuses_1mhzi_brownout:
	avrdude -c $(ISP) -p m8 -U lfuse:w:0xA1:m -U hfuse:w:0xD9:m

# Enable brown out detection at 2.7v and use 2MHz internal RC oscillator
fuses_2mhzi_brownout:
	avrdude -c $(ISP) -p m8 -U lfuse:w:0xA2:m -U hfuse:w:0xD9:m

# Enable brown out detection at 2.7v and use 4MHz internal RC oscillator
fuses_4mhzi_brownout:
	avrdude -c $(ISP) -p m8 -U lfuse:w:0xA3:m -U hfuse:w:0xD9:m

# Enable brown out detection at 2.7v and use 8MHz internal RC oscillator
fuses_8mhzi_brownout:
	avrdude -c $(ISP) -p m8 -U lfuse:w:0xA4:m -U hfuse:w:0xD9:m

# Enable brown out detection at 2.7v and use 4MHz external crystal
fuses_4mhze_brownout:
	avrdude -c $(ISP) -p m8 -U lfuse:w:0xAE:m -U hfuse:w:0xD9:m

# Erase
erase:
	avrdude -c $(ISP) -p m8 -e

# Load
load: main.hex
	avrdude -c $(ISP) -p m8 -e -U flash:w:main.hex

# Load but don't verify
load_noverify: main.hex
	avrdude -c $(ISP) -p m8 -e -V -U flash:w:main.hex

# Clean build files
clean:
	rm *.o *.out *.map *.hex
