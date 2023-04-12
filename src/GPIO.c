// GPIO.c
//
// Implementation of GPIO.h
//
// ELEC3106 Project
// HS, MR 3/4/23

#include "../include/GPIO.h"
#include "../include/settings.h"

#include <avr/io.h>

#include <stdbool.h>

#define PIN_PK_CLR PB4
#define PIN_SW PB6

// Peak clear is going to be PB4 - output
// Sample button will be PB6 - input

// DDXN sets data pin direction
// PORTXN is the value of the pin, read or write
// PINXN 

void GPIO_setup() {
    DDRB |= _BV(PIN_PK_CLR); // PB4 is output
    PORTB |= _BV(PIN_SW); // PB6 has pull-up
}

bool GPIO_sample() {
    // In debug modes just leave off
    return false;

    // Or on
    // return true;
    
    //return PINB & _BV(PIN_SW);
}

void GPIO_pk_clr_on() {
    PORTB |= _BV(PIN_PK_CLR);
}

void GPIO_pk_clr_off() {
    PORTB &= ~_BV(PIN_PK_CLR);
}

void GPIO_pk_clr_pulse() {
    
}