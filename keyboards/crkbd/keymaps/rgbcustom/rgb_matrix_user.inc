// !!! DO NOT ADD #pragma once !!! //

// Define the custom effect name
RGB_MATRIX_EFFECT(corne_layer_rgb)

// Implementation of the effect
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// QMK has a specific way to access headers
#include "quantum.h"
#include "action_layer.h"
#include "custom_keycodes.h"

// Define base RGB colors with strong values
#define COLOR_PURPLE      (RGB){150, 0, 255}    // Alpha keys
#define COLOR_YELLOW_GREEN (RGB){200, 255, 0}   // Modifiers
#define COLOR_ORANGE      (RGB){255, 120, 0}    // Numbers/special
#define COLOR_TEAL        (RGB){0, 255, 255}    // Arrows
#define COLOR_PURPLE_BLUE (RGB){100, 0, 255}    // Layer 1 symbols
#define COLOR_YELLOW      (RGB){255, 255, 0}    // Shifted symbols
#define COLOR_CYAN        (RGB){0, 255, 255}    // RGB controls/special keys
#define COLOR_RED         (RGB){255, 0, 0}      // Space/enter/boot
#define COLOR_PINK        (RGB){248, 152, 128}  // Pink orange
#define COLOR_BRIGHT_BLUE (RGB){50, 50, 255}    // Alt+arrow keys

// New colors for custom macros
#define COLOR_HOT_PINK    (RGB){255, 20, 147}   // Hot pink for bun macros
#define COLOR_WHITE       (RGB){255, 255, 255}  // White for settings
#define COLOR_GREEN       (RGB){0, 255, 0}      // Green for WhatsApp
#define COLOR_MAIL_BLUE   (RGB){0, 120, 255}    // Blue for mail
#define COLOR_REDDISH_PINK (RGB){255, 60, 100}  // Reddish pink for music
#define COLOR_REDDIT_ORANGE (RGB){255, 69, 0}    // Reddit orange, more red than yellow
#define COLOR_FERRARI_RED (RGB){220, 30, 5}      // Ferrari red
#define COLOR_LOCAL_NAVY (RGB){25, 25, 150}      // Localhost navy
#define COLOR_FEYN_INDIGO (RGB){110, 30, 190}    // Feyn chat indigo
#define COLOR_SECURITY_GOLD (RGB){230, 190, 40}  // Security gold
#define COLOR_BLACK       (RGB){0, 0, 0}         // Off/unused keys

// Key groups for easier checking
#define IS_ALPHA(kc) ((kc >= KC_Q && kc <= KC_P) || (kc >= KC_A && kc <= KC_L) || (kc >= KC_Z && kc <= KC_SLSH))
#define IS_MODIFIER(kc) (kc == KC_LSFT || kc == KC_RSFT || kc == KC_LCTL || kc == KC_LGUI || kc == KC_LALT)
#define IS_LAYER_KEY(kc) (kc == MO(1) || kc == MO(2) || kc == MO(3))
#define IS_ARROW(kc) (kc == KC_LEFT || kc == KC_DOWN || kc == KC_UP || kc == KC_RGHT)
#define IS_SPECIAL_KEY(kc) (kc == KC_TAB || kc == KC_ESC || kc == LGUI(KC_K) || kc == LGUI(KC_L) || kc == SGUI(KC_L))
#define IS_RGB_CONTROL(kc) (kc == RGB_TOG || kc == RGB_MOD || kc == RGB_HUI || kc == RGB_SAI || kc == RGB_VAI || kc == RGB_HUD || kc == RGB_SAD || kc == RGB_VAD)
#define IS_VOLUME_KEY(kc) (kc == KC_AUDIO_MUTE || kc == KC_AUDIO_VOL_DOWN || kc == KC_AUDIO_VOL_UP)
#define IS_MEDIA_KEY(kc) (kc == KC_MEDIA_PREV_TRACK || kc == KC_MEDIA_PLAY_PAUSE || kc == KC_MEDIA_NEXT_TRACK)
#define IS_BUN_MACRO(kc) (kc == BUN_DEV || kc == BUN_PRETTIER || kc == BUN_LINT || kc == VERCEL_DEPLOY)
#define IS_SC_MACRO(kc) (kc == SGUI(KC_3) || kc == SGUI(KC_4) || kc == SGUI(KC_5))
#define IS_CRITICAL_KEY(kc) (kc == KC_ENT || kc == KC_SPC || kc == KC_BSPC || kc == KC_DEL)

// Layer 1 specific color handling
static RGB get_layer1_color(uint16_t keycode) {
    // Number keys with shift-dependent colors
    if (keycode >= KC_1 && keycode <= KC_0) {
        return get_mods() & MOD_MASK_SHIFT ? COLOR_YELLOW : COLOR_PINK;
    }
    
    if (IS_SC_MACRO(keycode)) {
        return COLOR_REDDIT_ORANGE;
    }
    
    // Symbol keys
    if (keycode == KC_MINS || keycode == KC_EQL || 
        keycode == KC_LBRC || keycode == KC_RBRC || 
        keycode == KC_BSLS || keycode == KC_GRV) {
        return get_mods() & MOD_MASK_SHIFT ? COLOR_YELLOW : COLOR_ORANGE;
    }
    
    // Tab/Del/Backspace
    if (keycode == KC_TAB || keycode == KC_DEL || keycode == KC_BSPC) {
        return COLOR_RED;
    }
    
    // Navigation
    if (IS_ARROW(keycode)) {
        return COLOR_TEAL;
    } else if (keycode == LALT(KC_LEFT) || keycode == LALT(KC_RGHT)) {
        return COLOR_BRIGHT_BLUE;
    } else if (keycode == XXXXXXX) {
        return COLOR_BLACK;
    }
    
    // Default for layer 1
    return COLOR_PURPLE;
}

// Layer 2 app shortcut color handling
static RGB get_layer2_color(uint16_t keycode) {
    if (keycode == XXXXXXX) {
        return COLOR_BLACK;
    }
    if (keycode == KC_TRNS) {
        return COLOR_YELLOW_GREEN;
    }
    
    // App shortcut macros
    switch (keycode) {
        case SP_CURSOR:          return COLOR_TEAL;
        case SP_SAFARI:          return COLOR_BRIGHT_BLUE;
        case SP_TERMINAL:        return COLOR_PINK;
        case SP_SETTINGS:        return COLOR_WHITE;
        case SP_GITHUB:          return COLOR_PURPLE;
        case SP_WHATSAPP:        return COLOR_GREEN;
        case SP_MAIL:            return COLOR_MAIL_BLUE;
        case SP_MUSIC:           return COLOR_REDDISH_PINK;
        case SP_REDDIT:          return COLOR_REDDIT_ORANGE;
        case SP_YOUTUBE:         return COLOR_RED;
        case SP_MESSAGES:        return COLOR_YELLOW_GREEN;
        case SP_MOTORSPORT:      return COLOR_FERRARI_RED;
        case SP_LOCALHOST:       return COLOR_LOCAL_NAVY;
        case SP_FEYNCHAT:        return COLOR_FEYN_INDIGO;
        case SP_PASSWORD_MANAGER: return COLOR_SECURITY_GOLD;
        default:                 return COLOR_PURPLE;
    }
}

// Layer 3 RGB control color handling
static RGB get_layer3_color(uint16_t keycode) {
    if (IS_RGB_CONTROL(keycode)) {
        return COLOR_CYAN;
    } else if (keycode == QK_BOOT) {
        return COLOR_RED;
    } else if (IS_VOLUME_KEY(keycode)) {
        return COLOR_YELLOW_GREEN;
    } else if (IS_MEDIA_KEY(keycode)) {
        return COLOR_BRIGHT_BLUE;
    } else {
        return COLOR_BLACK;
    }
}

// Main function to get color based on keycode and layer
static RGB get_key_color(uint16_t keycode, uint8_t layer) {
    // Check highest priority keys first - these override layer settings
    if (IS_CRITICAL_KEY(keycode)) {
        return COLOR_RED;
    }
    
    if (IS_BUN_MACRO(keycode)) {
        return COLOR_HOT_PINK;
    }
    
    // Layer-specific coloring
    switch (layer) {
        case 1:
            return get_layer1_color(keycode);
        case 2:
            return get_layer2_color(keycode);
        case 3:
            return get_layer3_color(keycode);
    }
    
    // Base layer (0) coloring by key type
    if (IS_LAYER_KEY(keycode)) {
        return COLOR_YELLOW_GREEN;
    } else if (IS_ALPHA(keycode)) {
        return COLOR_PURPLE;
    } else if (IS_MODIFIER(keycode)) {
        return COLOR_YELLOW_GREEN;
    } else if (IS_SPECIAL_KEY(keycode)) {
        return COLOR_CYAN;
    }
    
    // Default color
    return COLOR_PURPLE;
}

// Apply brightness scaling to a color
static RGB scale_color(RGB color, float brightness) {
    RGB scaled = {
        .r = (uint8_t)((float)color.r * brightness),
        .g = (uint8_t)((float)color.g * brightness),
        .b = (uint8_t)((float)color.b * brightness)
    };
    return scaled;
}

// The main effect implementation
static bool corne_layer_rgb(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    
    // Get current layer and brightness scale
    uint8_t current_layer = get_highest_layer(layer_state);
    float brightness_scale = (float)rgb_matrix_get_val() / 255.0f;
    
    // Loop through all LEDs
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB color = COLOR_PURPLE;  // Default color
        
        // Find which key this LED belongs to
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if (g_led_config.matrix_co[row][col] == i) {
                    uint16_t keycode = keymap_key_to_keycode(current_layer, (keypos_t){col, row});
                    color = get_key_color(keycode, current_layer);
                    goto found_key; // Break out of both loops
                }
            }
        }
        
    found_key:
        // Apply brightness scaling
        color = scale_color(color, brightness_scale);
        
        // Set the color
        rgb_matrix_set_color(i, color.r, color.g, color.b);
    }
    
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS