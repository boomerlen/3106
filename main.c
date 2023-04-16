// main.c
//
// https://www.nongnu.org/avr-libc/user-manual/modules.html
//
// HS, MR, 3/4/23

#include <avr/io.h>

#include "include/FreqGen.h"
#include "include/ADC.h"

/////////////////
// Clock Setup //
/////////////////

// This flag is used to configure some of the low-level drivers
//#define F_CPU 1000000UL // Slow clock - 1MHz
// Now specified at compiler invokation

// #define F_CPU 8000000UL // Fast clock - 8MHz

// Set fuses appropriately

// Specified at compilation

// Slow mode
// Defaults are fine. Result is 1MHz CPU clock
FUSES = { 
    .low = FUSE_SELFPRGEN, // Enables self-programming
    .high = HFUSE_DEFAULT,
    .extended = 0x62,
};

///////////////
// Lock Bits //
///////////////

// I see no reason to enable any lock bits
// LB_MODE_1 does not enable any lock bits
LOCKBITS = LB_MODE_1;

// Freqgen N
#define FREQGEN_N 700

int main() {
    // On LED
    DDRB |= _BV(PB3);
    PORTB |= _BV(PB3);

    // Start frequency generator
    freqgen_setup();
    freqgen_set(FREQGEN_N);
    freqgen_enable();

    // If used, sample ADC and display results accordingly

    ADC_setup();

    // Calibrate ADC
    uint16_t no_metal = ADC_sample();

    // Output thresholds
    // Tune these
    uint16_t threshold[2] = {
        no_metal + 5, 
        no_metal + 15
    };

    // Light setup
    DDRA |= _BV(PA4);
    DDRA |= _BV(PA5);

    // Compare
    while (1) {
        uint16_t adc = ADC_sample();

        if (adc < threshold[0]) {
            // Both off
            PORTA &= ~(_BV(PA4) | _BV(PA5));
        } else if (adc < threshold[1]) {
            // One on
            PORTA &= ~(_BV(PA5));
            PORTA |= _BV(PA4);
        } else {
            // Both on
            PORTA |= _BV(PA4) | _BV(PA5);
        }
    }
}  
