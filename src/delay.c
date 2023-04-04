// delay.c
//
// Implementation of delay.h
//
// ELEC3106 Project
// HS, MR, 3/4/23

#include "../include/delay.h"

#include <util/delay_basic.h>

// Slow CPU clock
//#define F_CPU 1000000UL
// Defined at compiler invokation

// Fast CPU clock
// #define F_CPU 8000000UL

void delay_ms(int ms) {
    // Just a busy loop
    uint16_t top = ms * 250;

    _delay_loop_2(top);
}