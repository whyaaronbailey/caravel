// Copyright 2024 Kamran Shah (@whyaaronbailey)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_F17,  LCTL(KC_F13), KC_F21,  KC_F14,  LCTL(KC_F18), KC_F18,  LCTL(KC_F14), KC_F22,  KC_F15,  LCTL(KC_F19), LCTL(KC_F22), KC_F19,  LCTL(KC_F15), KC_F23,  LCTL(KC_F20), KC_F13,  KC_F16,  KC_F20,  LCTL(KC_F16), KC_F24,  MO(1),   LCTL(KC_F23), LCTL(KC_F17), LCTL(KC_F21)
    ),
    [1] = LAYOUT(
        KC_4,    KC_6,    KC_5,    KC_GRV,  KC_PGUP, KC_HOME, KC_END,  KC_UP,   LSFT(KC_TAB), KC_PGDN, _______, KC_LEFT, KC_RGHT, KC_DOWN, QK_BOOT, _______, _______, KC_7,    KC_9,    KC_8,    _______, _______, _______, _______
    )
};
