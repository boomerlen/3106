avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c main.c -o build/obj/main.o
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c src/ADC.c -o build/obj/ADC.o
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c src/FreqGen.c -o build/obj/FreqGen.o 
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -o build/bin/main.elf build/obj/main.o build/obj/ADC.o build/obj/FreqGen.o
avr-objdump -h -S build/bin/main.elf > build/bin/main.lst
avr-objcopy -j .text -j .data -O ihex build/bin/main.elf build/bin/main_txt.hex
avr-objcopy -j .fuse -O ihex build/bin/main.elf build/bin/main_fuse.hex
avr-objcopy -j .lock -O ihex build/bin/main.elf build/bin/main_lock.hex
python3 scripts/split_fuse.py build/bin/main_fuse.hex build/bin/main_