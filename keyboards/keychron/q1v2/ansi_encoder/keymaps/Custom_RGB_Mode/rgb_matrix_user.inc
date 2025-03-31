// !!! DO NOT ADD #pragma once !!! //

// Define the custom effect name
RGB_MATRIX_EFFECT(alpha_num_split)

// Implementation of the effect
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// QMK has a specific way to access headers - use quantum.h instead of individual headers
#include "quantum.h"
#include "custom_keycodes.h"

// Color definitions
typedef struct {
    HSV hsv;
    RGB rgb;
} KeyColor;

// Function to get keycode color
static RGB get_key_color(uint16_t keycode, const KeyColor* colors, uint8_t layer) {
    // First check if we're in MAC_FN layer
    if (layer == MAC_FN) {
        // App launcher macros
        if (keycode == SP_SAFARI || keycode == SP_GITHUB || 
            keycode == SP_TERMINAL || keycode == SP_WHATSAPP || 
            keycode == SP_SETTINGS || keycode == SP_MAIL) {
            return colors[8].rgb; // app_launcher_rgb
        }
        // Cursor-related macros
        else if (keycode == SP_CURSOR || keycode == MAC_CMDK || 
                 keycode == MAC_CMDL || keycode == MAC_CSSL) {
            return colors[7].rgb; // cursor_rgb
        }
        // VSCode panel macros
        else if (keycode == MAC_CMDB || keycode == MAC_CMDJ) {
            return colors[6].rgb; // vscode_rgb
        }
        // RGB control macros
        else if (keycode == RM_TOGG || keycode == RM_NEXT || keycode == RM_VALU || 
                 keycode == RM_HUEU || keycode == RM_SATU || keycode == RM_SPDU || 
                 keycode == RM_PREV || keycode == RM_VALD || keycode == RM_HUED || 
                 keycode == RM_SATD || keycode == RM_SPDD) {
            return colors[9].rgb; // rgb_control_rgb
        }
        // Development macros
        else if (keycode == BUN_DEV || keycode == BUN_LINT) {
            return colors[4].rgb; // bun_macro_rgb
        }
        // Special toggle
        else if (keycode == NK_TOGG) {
            return colors[10].rgb; // toggle_rgb
        }
        // Function layer itself
        else if (keycode == MO(MAC_FN)) {
            return colors[3].rgb; // special_rgb
        }
        // Keys that don't have specific assignments in MAC_FN
        else {
            return (RGB){0, 0, 0}; // Turn off RGB
        }
    }

    // ALPHA GROUP: A-Z keys
    if (keycode >= KC_A && keycode <= KC_Z) {
        return colors[0].rgb; // base_rgb
    }
    // NUMBER KEYS
    else if (keycode >= KC_1 && keycode <= KC_0) {
        return colors[0].rgb; // base_rgb
    }
    // BRACKET PAIRS
    else if (keycode == KC_LPRN || keycode == KC_RPRN) {
        return colors[0].rgb; // base_rgb
    }
    // ARROW KEYS
    else if (keycode == KC_LEFT || keycode == KC_RIGHT ||
             keycode == KC_UP || keycode == KC_DOWN) {
        return colors[0].rgb; // base_rgb
    }
    // PROGRAMMING PUNCTUATION
    else if (keycode == KC_DOT || keycode == KC_COMM || 
             keycode == KC_SCLN || keycode == KC_COLN || 
             keycode == KC_SLSH || keycode == KC_QUOT || keycode == KC_RBRC || keycode == KC_LBRC || keycode == KC_MINUS || keycode == KC_EQL) {
        return colors[1].rgb; // punct_rgb
    }
    // COMMAND KEYS
    else if (keycode == KC_LCTL || keycode == KC_RCTL || 
             keycode == KC_LALT || keycode == KC_RALT || 
             keycode == KC_LCMD || keycode == KC_RCMD || 
             keycode == KC_LOPT || keycode == KC_ROPT) {
        return colors[2].rgb; // alternate_rgb
    }
    // NAV/MOD KEYS
    else if (keycode == KC_BSPC || keycode == KC_BSLS ||
             keycode == KC_LSFT || keycode == KC_RSFT || 
             keycode == KC_CAPS || keycode == KC_TAB || keycode == KC_GRV) {
        return colors[2].rgb; // alternate_rgb
    }
    // FUNCTION KEYS and Delete
    else if ((keycode >= KC_F1 && keycode <= KC_F12 && 
             keycode != KC_F3 && keycode != KC_F4 && 
             keycode != KC_F10 && keycode != KC_F11 && 
             keycode != KC_F12) || keycode == KC_DEL || 
             keycode == KC_BRID || keycode == KC_BRIU || 
             keycode == RM_VALD || keycode == RM_VALU || 
             keycode == KC_MPRV || keycode == KC_MPLY || 
             keycode == KC_MNXT) {
        return colors[2].rgb; // alternate_rgb
    }
    // SPECIAL KEYS
    else if (keycode == KC_ENT || keycode == KC_SPC || 
             keycode == KC_ESC || keycode == QK_MOMENTARY) {
        return colors[3].rgb; // special_rgb
    }
    // SCREENSHOT MACRO
    else if (keycode == KC_F10 || keycode == KC_MUTE || keycode == MAC_CSCA) {
        return colors[5].rgb; // screenshot_rgb
    }
    // VSCODE PANEL MACROS
    else if (keycode == KC_F11 || keycode == KC_F12 || 
             keycode == KC_VOLD || keycode == KC_VOLU || keycode == MAC_CMDJ || keycode == MAC_CMDB) {
        return colors[6].rgb; // vscode_rgb
    }
    // CURSOR MACROS
    else if (keycode == KC_PGUP || keycode == KC_PGDN || 
             keycode == KC_HOME || keycode == MAC_CSSL || keycode == MAC_CMDK || keycode == MAC_CMDL) {
        return colors[7].rgb; // cursor_rgb
    }
    
    // Default color
    return colors[0].rgb;
}

static bool alpha_num_split(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    
    // Define all color sets with their HSV values and names
    KeyColor colors[11] = {
        {{190, 255, 255}, {0, 0, 0}}, // 0: base (bluish-purple)
        {{213, 255, 255}, {0, 0, 0}}, // 1: punct (slightly shifted from alpha)
        {{60, 255, 255},  {0, 0, 0}}, // 2: alternate (Greenish-yellow)
        {{0, 255, 255},   {0, 0, 0}}, // 3: special (Red)
        {{120, 255, 255}, {0, 0, 0}}, // 4: bun_macro (Orange/Amber)
        {{234, 255, 255}, {0, 0, 0}}, // 5: screenshot (pinkish-purple)
        {{170, 255, 255}, {0, 0, 0}}, // 6: vscode (Blue)
        {{135, 255, 255}, {0, 0, 0}}, // 7: cursor (Bluish-Cyan)
        {{135, 255, 255}, {0, 0, 0}}, // 8: app_launcher_rgb (Magenta)
        {{40, 255, 255}, {0, 0, 0}},  // 9: rgb_control_rgb (Bright Yellow)
        {{160, 255, 255}, {0, 0, 0}}  // 10: toggle_rgb (Turquoise)
    };
    
    // Adjust brightness based on current value setting
    uint8_t val = rgb_matrix_get_val();
    for (int i = 0; i < 11; i++) {
        colors[i].hsv.v = val;
        colors[i].rgb = hsv_to_rgb(colors[i].hsv);
    }
    
    // Get current layer
    uint8_t current_layer = get_highest_layer(layer_state);
    
    // Loop through all LEDs
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB color = colors[0].rgb;  // Default color
        bool found = false;
        
        // Find which key this LED belongs to
        for (uint8_t row = 0; row < MATRIX_ROWS && !found; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS && !found; col++) {
                if (g_led_config.matrix_co[row][col] == i) {
                    uint16_t keycode = keymap_key_to_keycode(current_layer, (keypos_t){col, row});
                    // Pass the current layer to get_key_color
                    color = get_key_color(keycode, colors, current_layer);
                    found = true;
                }
            }
        }
        
        // Set the color
        rgb_matrix_set_color(i, color.r, color.g, color.b);
    }
    
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
