// FreqGen.c
//
// Implementations of everything
//
// ELEC3106 Project
// HS, MR 30/3/23

#include "../include/FreqGen.h"

#include <inttypes.h>

#include <avr/interrupt.h>
#include <avr/io.h>

// This is implemented using tiny461a Timer (counter) 1
// This file does no conversion to achieve a desired frequency
// It simply takes the passed top value and places it directly
// into the required register.

// Decisions:
// 1. Output is going into OC1D
// 2. Want to use Normal Mode and "toggle Compare Output Mode"

ISR(TIMER1_COMPD_vect) {

}

void freqgen_setup() {
    // Clear prescaler
    //TCCR1B |= _BV(PSR1);

    // Set OCW1D to toggle on compare match mode
    TCCR1C |= _BV(COM1D0);

    // Ensure PLL is off 
    // (Using 1MHz system clock as source)
    PLLCSR |= _BV(PCKE) | _BV(PLLE);

    DDRB |= _BV(PB5);

    // Turn on output compare interrupt
    TIMSK |= _BV(OCIE1D);

    sei();
}

void freqgen_enable() {
    freqgen_disable();
    TCCR1B |= _BV(CS10);

}

void freqgen_disable() {
    TCCR1B &= ~(_BV(CS13) | _BV(CS12) | _BV(CS11) | _BV(CS10));
}

void freqgen_set(uint16_t top) {
    uint8_t high = (top & 0xFF00) >> 8;
    uint8_t low = (top & 0xFF);

    TC1H = high;
    OCR1C = top;
}