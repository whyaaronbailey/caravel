// Copyright 2024 Kamran Shah (@whyaaronbailey)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/*

GENERIC LAYOUT (buttons numbered in order)
                    ------              ------
          ------    |  1 |    ------    | 2  |   
          |  3 |    ------    |  4 |    ------     ------
          ------              ------               |  5 |
                    ------              ------     ------
                    | 6  |              | 7  |    
                    ------    ------    ------ 
          ------              |R 8 |               ------         
          |  9  |   ------    ------    ------     | 10 |    ------
          ------    |R 12|              |R 13|     ------    | 11 |
                    ------    ------    ------               |    | 
                              |R 14|                         |    |
------    ------              ------               ------    ------
| 15 |    | 16 |    ------              ------     | 17 |
------    ------    | 18 |    ------    | 19 |     ------
                    ------    | 20 |    ------               ------
          ------              ------               ------    | 22 |
          | 21 |                        ------     | 23 |    |    |
          ------                        | 24 |     |    |    |    |
                                        ------     ------    ------

DEFINED LAYOUT
                    ------              ------
          ------    |  1 |    ------    | 2  |   
          |  3 |    ------    |  4 |    ------     ------
          ------              ------               |  5 |
                    ------              ------     ------
                    | 6  |              | 7  |    
                    ------    ------    ------ 
          ------              |  8 |               ------         
          |  9  |   ------    ------    ------     | A  |    ------
          ------    |   |              |R 13|     ------    | 11 |
                    ------    ------    ------               |    | 
                              |R 14|                         |    |
------    ------              ------               ------    ------
| 15 |    |LSFT|    ------              ------     | 17 |
------    ------    | Z  |    ------    | C  |     ------
                    ------    | X  |    ------               ------
          ------              ------               ------    |SPC |
          |CTRL|                        ------     | B  |    |    |
          ------                        |ALT |     |    |    |    |
                                        ------     ------    ------


*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_1,    KC_3,    KC_2,    KC_ESC,  KC_R,    KC_Q,    KC_E,    KC_W,    KC_TAB,  KC_F,    KC_G,    KC_A,    KC_D,    KC_S,    KC_V,    MO(1),   KC_LSFT, KC_Z,    KC_C,    KC_X,    KC_LCTL, KC_SPC,  KC_B,    KC_LALT
    ),
    [1] = LAYOUT(
        KC_4,    KC_6,    KC_5,    KC_GRV,  KC_PGUP, KC_HOME, KC_END,  KC_UP,   LSFT(KC_TAB), KC_PGDN, _______, KC_LEFT, KC_RGHT, KC_DOWN, KC_0,    _______, _______, KC_7,    KC_9,    KC_8,    _______, _______, _______, _______
    )
};
