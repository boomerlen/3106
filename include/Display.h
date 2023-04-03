// Display.h
//
// Header file for standard display functions
//
// ELEC3106 project
// HS, MR, 3/4/23

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void display_setup();

void display_set_digit(uint8_t digit, uint8_t value);

void display_set_word(uint8_t word);

#endif // DISPLAY_H