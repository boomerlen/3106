// SPI_print.c
//
// Implementation of SPI_print.h
//
// ELEC3106 Project
// HS, MR 9/4/23

#include "../include/SPI_print.h"
#include "../include/settings.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay_basic.h>

#define PIN_DO PA1
#define PIN_DI PA0
#define PIN_SS PA3
#define PIN_UCK PA2

void serial_setup() {
    // SPI
    USICR |= _BV(USIWM0) | _BV(USICS1) | _BV(USICLK);

    // Setup pins
    DDRA |= _BV(PIN_DO) | _BV(PIN_SS) | _BV(PIN_UCK);
    PORTA |= _BV(PIN_SS);
}

void serial_print(char *data, uint8_t len) {
    // Add to buffer
    // Begin transfer is one is available
    // Just do the whole thing in one go in a slow loop
    // Don't seem to be able to do this asynchronously

    // Pull slave-select down
    PORTA &= ~_BV(PIN_SS);

    for (uint8_t i = 0; i < len; i++) {
        USIDR = data[i];
        
        // "Release" counter
        USISR |= _BV(USIOIF);
        
        // Strobe the clock until the counter overflow flag is set (?)
        while (USISR & _BV(USIOIF) != _BV(USIOIF)) {
            USICR |= _BV(USITC);

            // Slow the transfer down a tiny bit
            _delay_loop_1(4);
        }
    }

    PORTA |= _BV(PIN_SS);
}
