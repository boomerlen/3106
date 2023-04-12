// ADC.h
//
// High level ADC interface
// 
// ELEC3106 project
// HS, MR 30/3/23

#ifndef ADC_H
#define ADC_H

#include <inttypes.h>

// Note that PA0 has been selected as single-ended ADC
// input (deep inside the .c file)

void ADC_setup();

uint16_t ADC_sample();

#endif