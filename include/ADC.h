// ADC.h
//
// High level ADC interface
// 
// ELEC3106 project
// HS, MR 30/3/23

#ifndef ADC_H
#define ADC_H

#include <inttypes.h>

void ADC_setup();

uint16_t ADC_sample();

#endif