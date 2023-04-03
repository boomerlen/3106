// GPIO.h
//
// Header file for general pin operations
//
// ELEC3106 Project
// HS, MR 3/4/23

#ifndef GPIO_H
#define GPIO_H

#define GPIO_PK_CLR 1
#define GPIO_SAMPLE 2

#include <stdbool.h>

void GPIO_setup();

bool GPIO_sample();

void GPIO_pk_clr_on();

void GPIO_pk_clr_off();

void GPIO_pk_clr_pulse();

#endif // GPIO_H