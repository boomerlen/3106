// delay.c
//
// Implementation of delay.h
//
// ELEC3106 Project
// HS, MR, 3/4/23

#include "../include/delay.h"

#include <avr/io.h>

// Slow CPU clock
//#define F_CPU 1000000UL
// Defined at compiler invokation

// Fast CPU clock
// #define F_CPU 8000000UL

void delay_ms(int ms) {
    // Have to do some sort of nasty division type thing
    // Assuming slow CPU clock
    
    // Using /64 prescaling, one ms = 15.625 pulses
    // There will be some innacuraccy here with large counts, should be fine though
    // Hopefully relative error not so bad....
    
    // Max in 8 bits
    //const uint8_t max_ms_8bit = 16; 
    //const uint16_t max_ms_16bit = 4194;

    uint16_t top = ms * 16;

    uint8_t top_low = top & 0xFF;
    uint8_t top_high = (top >> 8) & 0xFF;

    // Ensure timer is halted
    TCCR0B |= _BV(TSM);
    TCCR0B |= _BV(PSR0);

    if (top_high != 0) {
        TCCR0A |= _BV(TCW0);
        OCR0B = top_high;
    } 

    OCR0A = top_low;

    // Ensure clock is initially cleared
    // If it isn't then oopsies
    TCNT0L = 0;
    TCNT0H = 0;

    // Prepare clock select
    TCCR0B |= _BV(CS02) | _BV(CS00);

    // Start clock
    TCCR0B &= ~_BV(TSM);

    // Wait for timer finished flag
    while (1) {
        uint8_t clock_done = TIFR & _BV(OCF0A);
        if (clock_done == _BV(OCF0A)) {
            break;
        }
    }
    
    // Timer done
    // Stop clock and clear timer buffer
    TCCR0B &= ~(_BV(CS02) | _BV(CS00));
    TCNT0L = 0;
    TCNT0H = 0;
}