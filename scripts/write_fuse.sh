avrdude -p t461a -c avrisp -b 19200 -P $TINY_PORT -U lfuse:w:build/bin/main_lfuse.hex:i
avrdude -p t461a -c avrisp -b 19200 -P $TINY_PORT -U hfuse:w:build/bin/main_hfuse.hex:i
avrdude -p t461a -c avrisp -b 19200 -P $TINY_PORT -U efuse:w:build/bin/main_efuse.hex:i