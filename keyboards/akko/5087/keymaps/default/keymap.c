/* Copyright (C) 2023 jonylee@hfd
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

#define CH_HOLD_TIME 1000

#define ON_PRESS(record, code) \
    do { \
        if ((record)->event.pressed) { \
            code; \
        } \
        return false; \
    } while (0)


#define CH_LAYOUT_OR_CAPS(record, code) \
    do { \
        static uint16_t ch_timer = 0; \
        if (record->event.pressed) { \
            ch_timer = timer_read(); \
            return false; \
        } else { \
            if (timer_elapsed(ch_timer) > CH_HOLD_TIME) { \
                tap_code(KC_CAPS); \
                if (host_keyboard_led_state().caps_lock) { \
                    rgb_matrix_set_color(50, 255, 0, 0); \
                } else { \
                    rgb_matrix_set_color(50, 0, 0, 0); \
                } \
            } else { \
                code; \
            } \
            return false; \
        } \
    } while (0)

enum __layers {
    WIN_0,
    WIN_1,
    WIN_2,
    MAC_0,
    MAC_1,
    MAC_2
};

enum custom_keycodes {
    L_RED = SAFE_RANGE,
    L_ORANGE,
    L_YELLOW,
    L_GREEN,
    L_CYAN,
    L_BLUE,
    L_PURPLE,
    L_WHITE,
    L_CYCLE_LR,
    L_CYCLE_A,
    ALT_SFT_OR_CAPS,
    CTL_SPC_OR_CAPS
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case L_RED:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_RED);
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            );
            break;
        case L_ORANGE:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_ORANGE);
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            );
            break;
        case L_YELLOW:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_YELLOW);
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            );
            break;
        case L_GREEN:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_GREEN);
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            );
            break;
        case L_CYAN:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_CYAN);
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            );
            break;
        case L_BLUE:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_BLUE);
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            );
            break;
        case L_PURPLE:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_PURPLE);
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            );
            break;
        case L_WHITE:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_WHITE);
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            );
            break;
        case L_CYCLE_LR:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_RED);
                rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
                rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
            );
            break;
        case L_CYCLE_A:
            ON_PRESS(record,
                rgb_matrix_sethsv(HSV_RED);
                rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
                rgb_matrix_set_speed(0);
            );
            break;

        case ALT_SFT_OR_CAPS:
            CH_LAYOUT_OR_CAPS(record,
                register_code(KC_LALT);
                wait_ms(5);
                tap_code(KC_LSFT);
                wait_ms(5);
                unregister_code(KC_LALT);
            );
            break;
        case CTL_SPC_OR_CAPS:
            CH_LAYOUT_OR_CAPS(record,
                register_code(KC_LCTL);
                wait_ms(5);
                tap_code(KC_SPC);
                wait_ms(5);
                unregister_code(KC_LCTL);
            );
            break;
    }

    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_0] = LAYOUT_tkl_ansi(
        KC_ESC,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_MUTE, KC_VOLD, KC_VOLU,
        KC_GRV,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
        ALT_SFT_OR_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,            KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, KC_RGUI, MO(WIN_1),       KC_RCTL,       KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_1] = LAYOUT_tkl_ansi(
        RM_TOGG, RM_VALD, RM_VALU, RM_SPDD, RM_SPDU, RM_PREV, RM_NEXT, _______, _______, _______,_______,  _______, _______,              KC_MPLY, KC_MPRV, KC_MNXT,
        L_CYCLE_LR, L_RED, L_ORANGE, L_YELLOW, L_GREEN, L_CYAN, L_BLUE, L_PURPLE, L_WHITE, L_CYCLE_A, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS,
        _______, _______,PDF(WIN_0),_______, _______, _______, _______, _______, _______, _______,_______,_______, _______, _______,      _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, PDF(MAC_0), _______, _______, _______,                   _______,           _______,
        _______, _______, _______,                   _______,                            _______, _______, _______,          _______,     _______, _______, _______),

    [WIN_2] = LAYOUT_tkl_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          _______,
        _______, _______, _______,                   _______,                            _______, _______, _______,       _______,    _______, _______, _______),

    [MAC_0] = LAYOUT_tkl_ansi(
        KC_ESC,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_MUTE, KC_VOLD, KC_VOLU,
        KC_GRV,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        CTL_SPC_OR_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,          KC_UP,
        KC_LCTL,    KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, KC_RALT, MO(MAC_1),       KC_RCTL,  KC_LEFT, KC_DOWN,   KC_RGHT),

    [MAC_1] = LAYOUT_tkl_ansi(
        RM_TOGG, RM_VALD, RM_VALU, RM_SPDD, RM_SPDU, RM_PREV, RM_NEXT, _______, _______, _______,_______,  _______, _______,              KC_MPLY, KC_MPRV, KC_MNXT,
        L_CYCLE_LR, L_RED, L_ORANGE, L_YELLOW, L_GREEN, L_CYAN, L_BLUE, L_PURPLE, L_WHITE, L_CYCLE_A, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS,
        _______, _______,PDF(WIN_0),_______, _______, _______, _______, _______, _______, _______,_______,_______, _______, _______,      _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, PDF(MAC_0), _______, _______, _______,                   _______,           _______,
        _______, _______, _______,                   _______,                            _______, _______, _______,          _______,     _______, _______, _______),

    [MAC_2] = LAYOUT_tkl_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          _______,
        _______, _______, _______,                   _______,                            _______, _______, _______,       _______,    _______, _______, _______)

};

