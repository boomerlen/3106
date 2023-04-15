// settings.h
// 
// Specifies compile-time constants
// used to set system parameters
//
// ELEC3106 Project
// HS, MR 6/4/23

#ifndef SETTINGS_H
#define SETTINGS_H

////////////////////
// Operating Mode //
////////////////////

// Enable the following define to use single-shot mode
// This technique involves using an ADC sample at a 
// single frequency near the expected 3dB point

// It is currently the only supported mode and must be enabled
//#define MODE_SINGLE_SHOT
// Defined at compile time.

///////////////////////////
// Pulse generator setup //
///////////////////////////

// freqgen_set(n) depends on peripheral clock frequency (and any prescaling)
// The output pulse generator is nominally 30kHz but will have
// quantisation errors as detailed in the table below.
// ----------------------------
// | F0    | n    | f_actual    |
// | 1MHz  | 16   | 31.25kHz    |
// | 8MHz  | 133  | 30.0752 kHz |
// | 64MHz | 1067 | 29.9906 kHz | --> Not realisable with 10-bit timer1
// ------------------------------

// Note that at 64MHz, the lowest clock rate deliverable is 31.25kHz (n = 1023).
// Consequently, 64MHz is too fast for single measurement operation centred at 30kHz
// It is also unnecessary.

// 64MHz is only useful in AC_Sweep() mode where greater frequency resolution is desired.

// Set the timer1 top given the clock and with reference to the above table below
// Aim for 25kHz
// We get 25kHz with n = 20 at F0 = 1MHz
#define FREQGEN_N 700

///////////////
// Pin Setup //
///////////////

// Blink pin
#define PIN_BLINK PB3

// Timer1 pin must be OC1D (PB5)

// Peak-Clear pin
#define PIN_PK_CLR PB4

// Sample button pin
#define PIN_SW PB6

///////////////////
// Serial Buffer //
///////////////////
#define SERIAL_BUF_LEN 16

#endif 