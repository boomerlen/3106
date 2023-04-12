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
#include <avr/interrupt.h>
#include <util/delay_basic.h>

#include "include/FreqGen.h"
#include "include/GPIO.h"
#include "include/delay.h"
#include "include/Display.h"
#include "include/blink.h"
//#include "include/SPI_print.h"
#include "include/settings.h"

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
            // Blink isn't so important as to interrupt this
            cli();

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

            // ADC_sample invokes low-noise mode
            // which shuts off system clocks etc

            // Sample ADC
            uint16_t adc_val = ADC_sample();

            // Clear peak holder
            GPIO_pk_clr_on();

            // Do some calculation
            convert(adc_val);

            // Output to display
            display_set_word(5);

            // Blink can keep on going
            sei();

            // Wait a bit to avoid triggering too many times in one press
            delay_ms(300);
        }
    }

}
#endif

void freqgen_test() {
    freqgen_setup();
    
    freqgen_set(FREQGEN_N);

    freqgen_enable();
}

void ADC_test() {
    // Continusouly sample ADC and compare against some voltage threshold
    ADC_setup();

    // Configure pin PA4 as cutoff-led
    DDRA |= _BV(PA4);

    // Note formula for actual conversion value:
    // ADC = VIN / VCC * 1024 (ideally, without any errors)

    uint16_t cutoff = 700; // About VCC/3

    while (1) {
        uint16_t adc_val = ADC_sample();

        if (adc_val > cutoff) {
            PORTA |= _BV(PA4);
        } else {
            PORTA &= ~_BV(PA4);
        }

        _delay_basic(100);
    }
}

int main() {

    blink_setup();

    freqgen_test();
    ADC_test();

#ifdef MODE_SINGLE_SHOT
    //ADC_SingleShot();
#else
    AC_Sweep();
#endif

}   