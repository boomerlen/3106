// blink.c
//
// Implementation of blink.h
//
// ELEC3106 Project
// HS, MR 6/4/23

#include "../include/blink.h"

#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>

static bool led_on = true;

ISR(TIMER0_COMPA_vect) {
    cli();
    TCNT0L = 0;
    TCNT0H = 0;

    if (led_on) {
        PORTB &= _BV(PIN_BLINK);
    } else {
        PORTB |= _BV(PIN_BLINK);
    }

    led_on = ~led_on;
    sei();
}

// Blink - flick on / off LED
void blink_setup() {
    // Have to do some sort of nasty division type thing
    // Assuming slow CPU clock
    
    // Using /1024 prescaling, one s = 977 pulses
    // There will be some innacuraccy here with large counts, should be fine though
    // Hopefully relative error not so bad....
    
    // Max in 8 bits
    //const uint8_t max_ms_8bit = 16; 
    //const uint16_t max_ms_16bit = 4194;

    // Compiler optimisations should remove most of this

    const uint16_t top = 977;

    uint8_t top_low = top & 0xFF;
    uint8_t top_high = (top >> 8) & 0xFF;

    // Ensure timer is halted
    TCCR0B |= _BV(TSM);
    TCCR0B |= _BV(PSR0);

    TCCR0A |= _BV(TCW0);
    OCR0B = top_high;

    OCR0A = top_low;

    // Ensure clock is initially cleared
    // If it isn't then oopsies
    TCNT0L = 0;
    TCNT0H = 0;

    // Enable interrupt 
    TIMSK |= _BV(OCIE0A);

    // Prepare clock select
    TCCR0B |= _BV(CS02) | _BV(CS00);

    // Start clock
    TCCR0B &= ~_BV(TSM);

    DDRB |= _BV(PIN_BLINK);
    
    PORTB |= _BV(PIN_BLINK);
}