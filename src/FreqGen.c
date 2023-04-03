// FreqGen.c
//
// Implementations of everything
//
// ELEC3106 Project
// HS, MR 30/3/23

#include "../include/FreqGen.h"

#include <inttypes.h>

#include <avr/io.h>

void _timerTopSet(uint16_t top) {
    // Split into upper and lower
    uint8_t high = (top & 0xFF00) > 8;
    uint8_t low = (top & 0xFF);

    TC1H = high;
    OCR1A = low;
}

void _timerFastMode() {
    PLLCSR |= _BV(PLLE);
    PLLCSR |= _BV(PCKE);
}

void _timerSlowMode() {
    PLLCSR &= ~_BV(PCKE);
}

void freqgen_setup() {
    TCCR1A |= _BV(COM1A0);
}

void freqgen_enable() {
    TCCR1B |= _BV(CS10);
}

void freqgen_disable() {
    TCCR1B &= ~(_BV(CS13) | _BV(CS12) | _BV(CS11) | _BV(CS10));
}

void freqgen_set(int f_khz) {
    // f is in KHz
    
    // Do some conversion
    uint16_t n = f_khz & 0xFFFF;

    _timerFastMode();
    _timerTopSet(n);
}