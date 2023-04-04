// main.c
//
// https://www.nongnu.org/avr-libc/user-manual/modules.html
//
// HS, MR, 3/4/23

/////////////////
// Mode Select //
/////////////////

// Comment this out for AC sweep
//#define MODE_SINGLE_SHOT
// Specified at compilation

#include <avr/io.h>

#include "include/FreqGen.h"
#include "include/GPIO.h"
#include "include/delay.h"
#include "include/Display.h"

#ifdef MODE_SINGLE_SHOT
#include "include/ADC.h"
#else
#include "include/AC.h"
#endif


/////////////////
// Clock Setup //
/////////////////

// This flag is used to configure some of the low-level drivers
//#define F_CPU 1000000UL // Slow clock - 1MHz
// Now specified at compiler invokation

// #define F_CPU 8000000UL // Fast clock - 8MHz

// Set fuses appropriately
#ifdef MODE_SINGLE_SHOT
// Specified at compilation

// Slow mode
// Defaults are fine. Result is 1MHz CPU clock
FUSES = { 
    .low = FUSE_SELFPRGEN, // Enables self-programming
    .high = HFUSE_DEFAULT,
    .extended = 0x62,
};
#else

// Fast mode
// Disable FUSE_CLKDIV8
// Result is 8MHz CPU clock from Internal Oscillator
FUSES = { 
    .low = FUSE_SELFPRGEN, // Enables self-programming
    .high = HFUSE_DEFAULT,
    .extended = (EFUSE_DEFAULT | FUSE_CLKDIV8),
};
#endif

///////////////////////////
// Pulse generator setup //
///////////////////////////

// freqgen_set(n) depends on peripheral clock frequency
// The output pulse generator is nominally 30kHz but will have
// quantisation errors as detailed in the table below.
// ----------------------------
// | F0    | n    | f_actual    |
// | 1MHz  | 16   | 31.25kHz    |
// | 8MHz  | 133  | 30.0752 kHz |
// | 64MHz | 1067 | 29.9906 kHz | --> Not realisable with 10-bit timer1
// ------------------------------

// Note that at 64MHz, the lowest clock rate deliverable is 31.25kHz.
// Consequently, 64MHz is too fast for single measurement operation centred at 30kHz
// It is also unnecessary.

// 64MHz is only useful in AC_Sweep() mode where greater frequency resolution is desired.

// Set the timer1 top given the clock and with reference to the above table below
#define FREQGEN_N 16

///////////////
// Lock Bits //
///////////////

// I see no reason to enable any lock bits
// LB_MODE_1 does not enable any lock bits
LOCKBITS = LB_MODE_1;

void convert(uint16_t adc_val) {
    return;
}

#ifndef MODE_SINGLE_SHOT
void AC_Sweep() {
    // Main function for the AC Sweep mode of operation
}
#endif

#ifdef MODE_SINGLE_SHOT
void ADC_SingleShot() {
    // Main function for the SingleShot mode of operation

    ADC_setup();
    freqgen_setup();
    GPIO_setup();
    display_setup();

    freqgen_set(FREQGEN_N);

    while (1) {
        if (GPIO_sample()) {
            // Disable peak holding
            GPIO_pk_clr_on();

            // Start frequency generator
            freqgen_enable();

            // Wait approx 1ms for steady state
            delay_ms(1);

            // Enable peak holding
            GPIO_pk_clr_off();

            // Wait approx 5ms to stabilise
            delay_ms(5);

            // Turn off freqgen to decrease noise
            freqgen_disable();

            // Here we would enable some low-noise mode

            // Sample ADC
            uint16_t adc_val = ADC_sample();

            // Clear peak holder
            GPIO_pk_clr_on();

            // Do some calculation
            convert(adc_val);

            // Output to display
            display_set_word(5);

            // Wait a bit to avoid triggering too many times in one press
            delay_ms(300);
        }
    }

}
#endif

int main() {

    // Test code
    GPIO_setup();

    while (1) {
        GPIO_pk_clr_on();
        delay_ms(1000);
        GPIO_pk_clr_off();
        delay_ms(1000);
    }

#ifdef MODE_SINGLE_SHOT
    //ADC_SingleShot();
#else
    AC_Sweep();
#endif

}   