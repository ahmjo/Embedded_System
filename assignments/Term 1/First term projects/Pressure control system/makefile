# Compiler prefix for arm-none-eabi tools
CC=arm-none-eabi-
CFLAGS=-gdwarf-2 -g -mcpu=cortex-m3

INCS=-I .
LIBS=

# Source and object files
SCR =$(wildcard *.c)
OBJ =$(SCR:.c=.o)
AS  =$(wildcard *.s)
ASOBJ=$(AS:.s=.o)

Project_name = Pressure_Controller

all:$(Project_name).bin
	@echo "=====Build is done====="

%.o:%.s	 
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o:%.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=map_file.map
	cp $(Project_name).elf $(Project_name).axf

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@


symbol:$(Project_name).elf
	$(CC)nm.exe $<

header:$(Project_name).elf
	$(CC)objdump.exe -h $<	 

asm:$(Project_name).elf
	$(CC)objdump.exe -d $<


clean_all:
	rm -f *.o *.elf *.bin *.map

clean:
	rm -f *.elf *.bin *.map