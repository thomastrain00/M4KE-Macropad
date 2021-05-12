/*
Copyright 2021 thomastrain00

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5454 // "TT"
#define PRODUCT_ID      0x3445 // "4E"
#define DEVICE_VER      0x0001
#define MANUFACTURER    thomastrain00
#define PRODUCT         M4KE
#define DESCRIPTION     A handwired 2x2 Macropad with a rotary encoder

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define MATRIX_ROWS 3
#define MATRIX_COLS 2

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
      { D4 }, \
    { B3 , B1 }, \
    { B6 , B2 } \
}
#define UNUSED_PINS

/* Rotary encoder */
#define ENCODERS_PAD_A { D1 }
#define ENCODERS_PAD_B { D0 }
#define ENCODER_RESOLUTION 4

/* LED layer indicators */
#define LAYER_INDICATOR_LED_0 B5	// red
#define LAYER_INDICATOR_LED_1 D7	// green
#define LAYER_INDICATOR_LED_2 C6	// blue

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

//speed for double tap
#define TAPPING_TERM 200