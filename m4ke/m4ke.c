/* Copyright 2021 thomastrain00
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "m4ke.h"

void keyboard_pre_init_kb(void) {
  // Set the layer LED IO as outputs
  setPinOutput(LAYER_INDICATOR_LED_0);
  setPinOutput(LAYER_INDICATOR_LED_1);
  setPinOutput(LAYER_INDICATOR_LED_2);
  
  keyboard_pre_init_user();
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    // disable pro micro LEDs
    DDRD &= ~(1<<5);
    PORTD &= ~(1<<5);

    DDRB &= ~(1<<0);
    PORTB &= ~(1<<0);

    //LED sequence on bootup
	writePinHigh(LAYER_INDICATOR_LED_0);
	writePinLow(LAYER_INDICATOR_LED_1);
	writePinLow(LAYER_INDICATOR_LED_2);
    wait_ms(250);
	writePinHigh(LAYER_INDICATOR_LED_0);
	writePinHigh(LAYER_INDICATOR_LED_1);
	writePinLow(LAYER_INDICATOR_LED_2);
    wait_ms(250);
	writePinLow(LAYER_INDICATOR_LED_0);
	writePinHigh(LAYER_INDICATOR_LED_1);
	writePinLow(LAYER_INDICATOR_LED_2);
    wait_ms(250);
	writePinLow(LAYER_INDICATOR_LED_0);
	writePinLow(LAYER_INDICATOR_LED_1);
	writePinHigh(LAYER_INDICATOR_LED_2);
	wait_ms(250);
	writePinLow(LAYER_INDICATOR_LED_0);
	writePinHigh(LAYER_INDICATOR_LED_1);
	writePinHigh(LAYER_INDICATOR_LED_2);
    wait_ms(250);
	writePinLow(LAYER_INDICATOR_LED_0);
	writePinLow(LAYER_INDICATOR_LED_1);
	writePinLow(LAYER_INDICATOR_LED_2);
    wait_ms(250);
    matrix_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
  // Layer LEDs act as binary indication of current layer
	switch(get_highest_layer(state))
	{
		case 0:	//red
			writePinHigh(LAYER_INDICATOR_LED_0);
			writePinLow(LAYER_INDICATOR_LED_1);
			writePinLow(LAYER_INDICATOR_LED_2);
			break;
		case 1:	//yellow
			writePinHigh(LAYER_INDICATOR_LED_0);
			writePinHigh(LAYER_INDICATOR_LED_1);
			writePinLow(LAYER_INDICATOR_LED_2);
			break;
		case 2:	//green
			writePinLow(LAYER_INDICATOR_LED_0);
			writePinHigh(LAYER_INDICATOR_LED_1);
			writePinLow(LAYER_INDICATOR_LED_2);
			break;
		case 3:	//blue
			writePinLow(LAYER_INDICATOR_LED_0);
			writePinLow(LAYER_INDICATOR_LED_1);
			writePinHigh(LAYER_INDICATOR_LED_2);
			break;
		case 4: //teal
			writePinLow(LAYER_INDICATOR_LED_0);
			writePinHigh(LAYER_INDICATOR_LED_1);
			writePinHigh(LAYER_INDICATOR_LED_2);
			wait_ms(3000);
			break;
		default:
			break;
	}
  return state;
}

void suspend_power_down_kb(void) {
  // Shutdown the layer LEDs
  writePinLow(LAYER_INDICATOR_LED_0);
  writePinLow(LAYER_INDICATOR_LED_1);
  writePinLow(LAYER_INDICATOR_LED_2);
}