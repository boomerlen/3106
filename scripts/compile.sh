avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c main.c -o build/obj/main.o
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c src/ADC.c -o build/obj/ADC.o
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c src/FreqGen.c -o build/obj/FreqGen.o 
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c src/AC.c -o build/obj/AC.o
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c src/delay.c -o build/obj/delay.o
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c src/Display.c -o build/obj/Display.o
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c src/GPIO.c -o build/obj/GPIO.o
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -c src/blink.c -o build/obj/blink.o
avr-gcc -g -mmcu=attiny461a -O3 -DMODE_SINGLE_SHOT -DF_CPU=1000000LU -o build/bin/main.elf build/obj/main.o build/obj/ADC.o build/obj/FreqGen.o build/obj/AC.o build/obj/delay.o build/obj/Display.o build/obj/GPIO.o build/obj/blink.o
avr-objdump -h -S build/bin/main.elf > build/bin/main.lst
avr-objcopy -j .text -j .data -O ihex build/bin/main.elf build/bin/main_txt.hex
avr-objcopy -j .fuse -O ihex build/bin/main.elf build/bin/main_fuse.hex
avr-objcopy -j .lock -O ihex build/bin/main.elf build/bin/main_lock.hex
python3 scripts/split_fuse.py build/bin/main_fuse.hex build/bin/main_