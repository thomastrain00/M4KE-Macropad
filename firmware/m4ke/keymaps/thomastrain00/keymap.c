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

enum keyboard_layers{
    _MEDIA = 0,
    _ONENOTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* MEDIA LAYER
  *       ,-----------.
  *       |  KC_MUTE  |
  * ,-----+-----------+-----.
  * |  KC_MPRV  |  KC_MNXT  |
  * |-----------+-----------|
  * |  KC_MPLY  |   KC_NO   |
  * `-----------+-----------'
  */
      [_MEDIA] = LAYOUT(
          KC_MUTE, \
          KC_MPRV, KC_MNXT, \
          KC_MPLY, TG(_ONENOTE) \
          ),

  /* ONENOTE LAYER
  *         ,----------.
  *         |  KC_DEL  |
  * ,-------+----------+----------.
  * |     C(Z)   |      C(Y)      |
  * |------------+----------------|
  * |   KC_ESC   |  TG(_ONENOTE)  |
  * `------------+----------------'
  */
      [_ONENOTE] = LAYOUT(
          KC_DEL, \
          C(Z) , C(Y) \
          KC_ESC, TG(_ONENOTE) \
          )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
      if (IS_LAYER_ON(_ONENOTE))
      {
          if (clockwise)
          {
            tap_code(MEH(KC_PLUS));
          }
          else
          {
            tap_code(MEH(KC_MINS));
          }

      }

      else {
          if (clockwise) 
          {
            tap_code(KC_VOLU);
          }
         else 
         {
            tap_code(KC_VOLD);
         }
      }
       
    } 
}