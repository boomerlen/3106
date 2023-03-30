avr-gcc -g -mmcu=attiny461a -c main.c
avr-gcc -g -mmcu=attiny461a -o main.elf main.o
avr-objdump -h -S main.elf > main.lst
avr-objcopy -j .text -j .data -O ihex main.elf main_txt.hex
avr-objcopy -j .fuse -O ihex main.elf main_fuse.hex
avr-objcopy -j .lock -O ihex main.elf main_lock.hex