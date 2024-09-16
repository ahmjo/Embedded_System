CC=arm-none-eabi
CFLAGS=-gdwarf-2 -g -mcpu=cortex-m4 -mthumb -std=c99 
INGS=-I .
LIBS=

SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
As= $(wildcard *.s)
AsOBJ= $(As:.s=.o)

proj_name= lab3_cortex_m4

all: $(proj_name).bin
	@echo "======done====="

%.o: %.c
	$(CC)-gcc $(CFLAGS) $(INGS) -c $<  -o $@

%.o: %.s
	$(CC)-as $< -o $@

$(proj_name).elf: $(OBJ) $(AsOBJ)
	$(CC)-ld -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -MAP=MAP_file.map
	cp $(proj_name).elf $(proj_name).axf

$(proj_name).bin: $(proj_name).elf
	$(CC)-objcopy -O binary $<  $@

clean_all:
	rm -f *.o *.elf *.bin *.map

clean:
	rm -f *.elf *.bin *.map