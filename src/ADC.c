// ADC.c
//
// Implementations of everything
//
// ELEC3106 Project
// HS, MR 30/3/23

#ifdef MODE_SINGLE_SHOT

#include "../include/ADC.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

ISR(ADC_vect) {
    // Turn off sleep mode
    sleep_disable();
}

void ADC_setup() {
    // Enable ADC interrupt
    ADCSRA |= _BV(ADIE);

    // Reference set to VCC
    // Set ADC input
    ADMUX |= 0x00; // Single-ended ADC0 (PA0)


    // Set clock prescaling
    // See datasheet section 15.5 (pg 144)
    // Want between 50-200kHz from 1MHz.
    // Division by 8 will achieve this.
    ADCSRA |= _BV(ADPS1) | _BV(ADPS0);
}

uint16_t ADC_sample() {
    // Enable ADC
    ADCSRA |= _BV(ADEN);

    // Prepare for sleep
    sleep_enable();
    MCUCR |= _BV(SM0); // ADC noise reduction mode
    sei();

    // Start conversion
    ADCSRA |= _BV(ADSC);

    // Enable sleep mode (will be woken by ADC interrupt)
    sleep_mode();

    // Wait for SE to be clear
    // Should happen immediately if all the sleep + wake stuff has worked
    while (1) {
        uint8_t se = (MCUCR & _BV(SE));
        if (se == _BV(SE)) {
            break;
        }
    }

    // Extract data
    // ADCL must be read first.
    uint8_t adc_lower = ADCL;
    uint8_t adc_upper = ADCH;

    // Data is right justified
    uint16_t adc_result = (adc_upper << 6) + adc_lower;
    return adc_result;
}

#endif