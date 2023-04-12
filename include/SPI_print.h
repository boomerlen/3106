// SPI_print.h
//
// Driver for serial data transfer over SPI
//
// ELEC3106 Project
// HS, MR 9/4/23

#ifndef SPI_PRINT_H
#define SPI_PRINT_H

#include <stdint.h>
#include "settings.h"

void serial_print(char *data, uint8_t len);

void serial_setup();
#endif // SPI_PRINT_H