###############################################################################
# Makefile for the project AVR_GUI
###############################################################################

## General Flags
PROJECT = AVR_GUI
MCU = atxmega128a3
TARGET = AVR_GUI.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                                                     -DF_CPU=32000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=AVR_GUI.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = main.o TFT_Driver.o clksys_driver.o spi_driver.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) AVR_GUI.hex AVR_GUI.eep AVR_GUI.lss size

## Compile
main.o: ../USER/main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

TFT_Driver.o: ../USER/TFT_Driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

clksys_driver.o: ../USER/clksys_driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

spi_driver.o: ../USER/spi_driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) AVR_GUI.elf dep/* AVR_GUI.hex AVR_GUI.eep AVR_GUI.lss AVR_GUI.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

