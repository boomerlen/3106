avrdude -p t461a -c avrisp -b 19200 -P $TINY_PORT -U flash:w:main_txt.hex:i