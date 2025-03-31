// !!! DO NOT ADD #pragma once !!! //

// Define the custom effect name - keeping the same name for compatibility
RGB_MATRIX_EFFECT(alpha_num_split)

// Implementation of the effect
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// QMK has a specific way to access headers - use quantum.h instead of individual headers
#include "quantum.h"

// Color definitions
typedef struct {
    HSV hsv;
    RGB rgb;
} KeyColor;

// Function to get keycode color
static RGB get_key_color(uint16_t keycode, const KeyColor* colors, uint8_t layer) {
    // RED KEYS: Layer toggle and Enter key
    if (keycode == KC_PENT || keycode == TG(2)) {
        return colors[3].rgb; // special_rgb (Red)
    }
    // GREEN KEYS: Operators, decimal point, and 0
    else if (keycode == KC_PSLS || keycode == KC_PAST || 
             keycode == KC_PMNS || keycode == KC_PPLS || 
             keycode == KC_PDOT || keycode == KC_P0 ||
             keycode == LT(1, KC_PMNS)) {
        return colors[2].rgb; // alternate_rgb (Green)
    }
    // NUMPAD KEYS: 1-9 with base color
    else if (keycode >= KC_P1 && keycode <= KC_P9) {
        return colors[0].rgb; // base_rgb (bluish-purple)
    }
    
    // Default color for any other keys
    return colors[0].rgb;
}

static bool alpha_num_split(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    
    // Define color sets with their HSV values and names
    KeyColor colors[11] = {
        {{190, 255, 255}, {0, 0, 0}}, // 0: base (bluish-purple) - for numpad 1-9
        {{213, 255, 255}, {0, 0, 0}}, // 1: punct (slightly shifted from alpha)
        {{60, 255, 255}, {0, 0, 0}}, // 2: alternate (Green) - for operators, 0, decimal
        {{0, 255, 255},   {0, 0, 0}}, // 3: special (Red) - for enter and layer toggle
        {{30, 255, 255},  {0, 0, 0}}, // 4: bun_macro (Orange/Amber)
        {{234, 255, 255}, {0, 0, 0}}, // 5: screenshot (pinkish-purple)
        {{170, 255, 255}, {0, 0, 0}}, // 6: vscode (Blue)
        {{135, 255, 255}, {0, 0, 0}}, // 7: cursor (Bluish-Cyan)
        {{255, 255, 255}, {0, 0, 0}}, // 8: app_launcher_rgb
        {{255, 255, 255}, {0, 0, 0}}, // 9: rgb_control_rgb
        {{255, 255, 255}, {0, 0, 0}}  // 10: toggle_rgb
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
