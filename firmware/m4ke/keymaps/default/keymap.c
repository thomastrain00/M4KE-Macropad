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

#include QMK_KEYBOARD_H

enum {
  TD_TG0_TG1 = 0,
  TD_TG1_TG2,
  TD_TG2_TG3,
  TD_TG3_TG4,
  TD_TG4_TG0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_TG0_TG1] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_TRNS, 1),
  [TD_TG1_TG2] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_TRNS, 2),
  [TD_TG2_TG3] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_TRNS, 3),
  [TD_TG3_TG4] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_TRNS, 4),
  [TD_TG4_TG0] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_TRNS, 0),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_MUTE, 
    KC_MPRV, KC_MNXT, 
    KC_MPLY, TD(TD_TG0_TG1)
  ),

  [1] = LAYOUT(
    KC_TRNS, 
    KC_TRNS, KC_TRNS, 
    KC_TRNS, TD(TD_TG1_TG2)
  ),

  [2] = LAYOUT (
    KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS, TD(TD_TG2_TG3)
  ),

  [3] = LAYOUT (
    KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS, TD(TD_TG3_TG4)
  ),

  [4] = LAYOUT (
    KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS, TD(TD_TG4_TG0)
  ),

};

void encoder_update_user(uint8_t index, bool clockwise) {
  /*  Custom encoder control - handles CW/CCW turning of encoder
   *  Default behavior:
   *    main layer:
   *       CW: volume up
   *      CCW: volume down
   *    second layer:
   *       CW: 
   *      CCW: 
   *	
   */
  if (index == 0) 
  {
    if(IS_LAYER_ON(1))
    {
        if (clockwise) {
          tap_code16(C(KC_Y));
        } else {
          tap_code16(C(KC_Z));
        }
    }
    else
    {
        // main layer - volume up (CW) and down (CCW)
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
    }
  }
}
