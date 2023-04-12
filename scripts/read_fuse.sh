avrdude -p t461a -c avrisp -b 19200 -P $TINY_PORT -U lfuse:r:lfuse.hex:i
avrdude -p t461a -c avrisp -b 19200 -P $TINY_PORT -U hfuse:r:hfuse.hex:i
avrdude -p t461a -c avrisp -b 19200 -P $TINY_PORT -U efuse:r:efuse.hex:i
