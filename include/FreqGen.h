// FreqGen.h
//
// High-level frequency generator interface
//
// ELEC3106 Project
// HS, MR 30/3/23

#ifndef FREQGEN_H
#define FREQGEN_h

#include <inttypes.h>

void freqgen_setup();

void freqgen_enable();

void freqgen_disable();

void freqgen_set(uint16_t top);

#endif