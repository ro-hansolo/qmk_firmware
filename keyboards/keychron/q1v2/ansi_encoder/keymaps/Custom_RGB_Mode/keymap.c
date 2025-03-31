/* Copyright 2023 @ Keychron (https://www.keychron.com)
 * Copyright 2024 @ bbdeeplearning.systems (https://bbdeeplearning.systems)
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
#include "custom_keycodes.h"

// clang-format off

// enum layers{
//     MAC_BASE,
//     MAC_FN,
//     WIN_BASE,
//     WIN_FN
// };

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)
#define RGB_CUSTOM_ALPHA_NUM RGB_MATRIX_CUSTOM_alpha_num_split

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  BUN_DEV, BUN_LINT, RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  MAC_CSCA,  MAC_CMDB,  MAC_CMDJ,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            MAC_CMDK,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            MAC_CMDL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             MAC_CSSL,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        _______,  KC_F1,    KC_F2,    SP_SAFARI, SP_GITHUB, KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   SP_CURSOR,   SP_TERMINAL,   _______,            RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            SP_WHATSAPP,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            SP_SETTINGS,
        _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            SP_MAIL,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                             _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCMD,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,            RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),
};

// Helper functions for common key combinations
static void tap_gui_key(uint8_t keycode) {
    register_code(KC_LGUI);
    register_code(keycode);
    unregister_code(keycode);
    unregister_code(KC_LGUI);
}

static void tap_gui_shift_key(uint8_t keycode) {
    register_code(KC_LGUI);
    register_code(KC_LSFT);
    register_code(keycode);
    unregister_code(keycode);
    unregister_code(KC_LSFT);
    unregister_code(KC_LGUI);
}

static void open_with_spotlight(const char *app_name) {
    // Open spotlight
    tap_gui_key(KC_SPC);
    
    // Type app name and press enter
    wait_ms(50); // Reduced from 100ms for better performance
    SEND_STRING(app_name);
    tap_code(KC_ENT);
}

// Macro implementations
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;  // Early return for key releases
    }

    switch (keycode) {
        case MAC_CMDK:
            tap_gui_key(KC_K);
            return false;
        
        case MAC_CMDL:
            tap_gui_key(KC_L);
            return false;
        
        case MAC_CSSL:
            tap_gui_shift_key(KC_L);
            return false;

        case MAC_CSCA:
            tap_gui_shift_key(KC_5);
            return false;

        case MAC_CMDB:
            tap_gui_key(KC_B);
            return false;

        case MAC_CMDJ:
            tap_gui_key(KC_J);
            return false;

        case BUN_DEV:
            SEND_STRING("bun dev");
            return false;

        case BUN_LINT:
            SEND_STRING("bun lint");
            return false;

        // Spotlight search commands
        case SP_CURSOR:
            open_with_spotlight("cursor");
            return false;

        case SP_SAFARI:
            open_with_spotlight("safari");
            return false;

        case SP_GITHUB:
            open_with_spotlight("github desktop");
            return false;

        case SP_TERMINAL:
            open_with_spotlight("iterm");
            return false;

        case SP_WHATSAPP:
            open_with_spotlight("whatsapp");
            return false;

        case SP_SETTINGS:
            open_with_spotlight("system settings");
            return false;

        case SP_MAIL:
            open_with_spotlight("mail");
            return false;

        default:
            return true;
    }
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU)},
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU)}
};
#endif // ENCODER_MAP_ENABLE
