// !!! DO NOT ADD #pragma once !!! //

// Define the custom effect name
RGB_MATRIX_EFFECT(corne_layer_rgb)

// Implementation of the effect
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// QMK has a specific way to access headers
#include "quantum.h"
#include "action_layer.h"
#include "custom_keycodes.h"

// Color definitions
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

// Base colors with descriptive names
static const rgb_color_t COLORS = {
    .PURPLE = {150, 0, 255},         // Alpha keys
    .YELLOW_GREEN = {200, 255, 0},   // Modifiers
    .ORANGE = {255, 120, 0},         // Numbers/special
    .TEAL = {0, 255, 255},           // Arrows
    .PURPLE_BLUE = {100, 0, 255},    // Layer 1 symbols
    .YELLOW = {255, 255, 0},         // Shifted symbols
    .CYAN = {0, 255, 255},           // RGB controls/special keys
    .RED = {255, 0, 0},              // Space/enter/boot
    .PINK = {248, 152, 128},         // Pink orange
    .BRIGHT_BLUE = {50, 50, 255},    // Alt+arrow keys
    
    // App shortcut colors
    .HOT_PINK = {255, 20, 147},      // Hot pink for bun macros
    .WHITE = {255, 255, 255},        // White for settings
    .GREEN = {0, 255, 0},            // Green for WhatsApp
    .MAIL_BLUE = {0, 120, 255},      // Blue for mail
    .REDDISH_PINK = {255, 60, 100},  // Reddish pink for music
    .REDDIT_ORANGE = {255, 69, 0},   // Reddit orange
    .FERRARI_RED = {220, 30, 5},     // Ferrari red
    .LOCAL_NAVY = {25, 25, 150},     // Localhost navy
    .FEYN_INDIGO = {110, 30, 190},   // Feyn chat indigo
    .SECURITY_GOLD = {230, 190, 40}, // Security gold
    .BLACK = {0, 0, 0}               // Off state
};

// Key category check macros
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

// Layer-specific color handling functions
static rgb_color_t get_layer1_color(uint16_t keycode) {
    // Number keys with shift-dependent colors
    if (keycode >= KC_1 && keycode <= KC_0) {
        return get_mods() & MOD_MASK_SHIFT ? COLORS.YELLOW : COLORS.PINK;
    }
    
    if (IS_SC_MACRO(keycode)) {
        return COLORS.REDDIT_ORANGE;
    }
    
    // Symbol keys
    if (keycode == KC_MINS || keycode == KC_EQL || 
        keycode == KC_LBRC || keycode == KC_RBRC || 
        keycode == KC_BSLS || keycode == KC_GRV) {
        return get_mods() & MOD_MASK_SHIFT ? COLORS.YELLOW : COLORS.ORANGE;
    }
    
    // Tab/Del/Backspace
    if (keycode == KC_TAB || keycode == KC_DEL || keycode == KC_BSPC) {
        return COLORS.RED;
    }
    
    // Navigation
    if (IS_ARROW(keycode)) {
        return COLORS.TEAL;
    } else if (keycode == LALT(KC_LEFT) || keycode == LALT(KC_RGHT)) {
        return COLORS.BRIGHT_BLUE;
    } else if (keycode == XXXXXXX) {
        return COLORS.BLACK;
    }
    
    // Default for layer 1
    return COLORS.PURPLE;
}

static rgb_color_t get_layer2_color(uint16_t keycode) {
    if (keycode == XXXXXXX) {
        return COLORS.BLACK;
    }
    if (keycode == KC_TRNS) {
        return COLORS.YELLOW_GREEN;
    }
    
    // App shortcut macros
    switch (keycode) {
        case SP_CURSOR:          return COLORS.TEAL;
        case SP_SAFARI:          return COLORS.BRIGHT_BLUE;
        case SP_TERMINAL:        return COLORS.PINK;
        case SP_SETTINGS:        return COLORS.WHITE;
        case SP_GITHUB:          return COLORS.PURPLE;
        case SP_WHATSAPP:        return COLORS.GREEN;
        case SP_MAIL:            return COLORS.MAIL_BLUE;
        case SP_MUSIC:           return COLORS.REDDISH_PINK;
        case SP_REDDIT:          return COLORS.REDDIT_ORANGE;
        case SP_YOUTUBE:         return COLORS.RED;
        case SP_MESSAGES:        return COLORS.YELLOW_GREEN;
        case SP_MOTORSPORT:      return COLORS.FERRARI_RED;
        case SP_LOCALHOST:       return COLORS.LOCAL_NAVY;
        case SP_FEYNCHAT:        return COLORS.FEYN_INDIGO;
        case SP_PASSWORD_MANAGER: return COLORS.SECURITY_GOLD;
        default:                 return COLORS.PURPLE;
    }
}

static rgb_color_t get_layer3_color(uint16_t keycode) {
    if (IS_RGB_CONTROL(keycode)) {
        return COLORS.CYAN;
    } else if (keycode == QK_BOOT) {
        return COLORS.RED;
    } else if (IS_VOLUME_KEY(keycode)) {
        return COLORS.YELLOW_GREEN;
    } else if (IS_MEDIA_KEY(keycode)) {
        return COLORS.BRIGHT_BLUE;
    } else {
        return COLORS.BLACK;
    }
}

// Main function to get color based on keycode and layer
static rgb_color_t get_key_color(uint16_t keycode, uint8_t layer) {
    // Check highest priority keys first - these override layer settings
    if (IS_CRITICAL_KEY(keycode)) {
        return COLORS.RED;
    }
    
    if (IS_BUN_MACRO(keycode)) {
        return COLORS.HOT_PINK;
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
        return COLORS.YELLOW_GREEN;
    } else if (IS_ALPHA(keycode)) {
        return COLORS.PURPLE;
    } else if (IS_MODIFIER(keycode)) {
        return COLORS.YELLOW_GREEN;
    } else if (IS_SPECIAL_KEY(keycode)) {
        return COLORS.CYAN;
    }
    
    // Default color
    return COLORS.PURPLE;
}

// Apply brightness scaling to a color
static rgb_color_t scale_color(rgb_color_t color, float brightness) {
    rgb_color_t scaled = {
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
        rgb_color_t color = COLORS.PURPLE;  // Default color
        
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