/*
Copyright 2012,2013 gezhaoyou <gezhaoyou@126.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#define RGB_CUSTOM_ALPHA_NUM RGB_MATRIX_CUSTOM_alpha_num_split

enum custom_keycodes {
    BUN_PRETTIER = SAFE_RANGE,
    VERCEL_DEPLOY,
    ADD_JSDOC,
    ISSUE_FIX,
    ISSUE_DESCRIBE,
    DEV_LOG,
    PIP_INSTALL,
    PIP_FREEZE,
    SP_FEYNCHAT,
    SP_LOCALHOST,
    REACT_FN,
    REACT_FN_PROPS,
    CN_LG,
    FRMT_JS,
    USE_STATE,
    USE_CONTEXT,
    USE_EFFECT_HOOK,
    PIP_REQ,
    PY_TRY,
    PY_PRINT,
    TF_INIT,
    TF_PLAN,
    TF_APPLY,
    TF_DESTROY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_numpad_5x4(
        TG(2),                  KC_PSLS,                KC_PAST,        LT(1, KC_PMNS),
        KC_P7,                  KC_P8,                  KC_P9,
        KC_P4,                  KC_P5,                  KC_P6,          KC_PPLS,
        KC_P1,                  KC_P2,                  KC_P3,
                                KC_P0,                  KC_PDOT,        KC_PENT),
   [1] = LAYOUT_numpad_5x4(
        KC_TRNS,                KC_CALCULATOR,          KC_BSPC,        KC_TRNS,
        RM_NEXT,                RM_VALU,                RM_HUEU,
        RM_SPDD,                RM_TOGG,                RM_SPDU,        QK_BOOT,
        RM_PREV,                RM_VALD,                RM_HUED,
                                KC_TRNS,                KC_TRNS,        EE_CLR),
   [2] = LAYOUT_numpad_5x4(
        TG(2),                  FRMT_JS,                CN_LG,          TG(3),
        USE_CONTEXT,            REACT_FN_PROPS,         REACT_FN,
        DEV_LOG,                USE_EFFECT_HOOK,        USE_STATE,      BUN_PRETTIER,
        ADD_JSDOC,              ISSUE_DESCRIBE,         ISSUE_FIX,
                                SP_FEYNCHAT,            SP_LOCALHOST,   VERCEL_DEPLOY),
    [3] = LAYOUT_numpad_5x4(
        TG(2),                  KC_TRNS,                KC_TRNS,        TG(3),
        TF_PLAN,                TF_APPLY,               TF_DESTROY,
        TF_INIT,                PY_PRINT,               PY_TRY,         KC_TRNS,
        PIP_INSTALL,            PIP_FREEZE,             PIP_REQ,
                                KC_TRNS,                KC_TRNS,        KC_TRNS),                
};

bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case 1:
            rgb_matrix_set_color_all(255, 255, 0); // Yellow
            break;
        case 2:
            rgb_matrix_set_color_all(75, 110, 130); // Muted Blue Gray
            
            // Highlight specific keys with different colors
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    // Check if key is P1, P2, P3, or P4
                    if ((row == 3 && col == 0) || // P1
                        (row == 3 && col == 1) || // P2
                        (row == 3 && col == 2) || // P3
                        (row == 2 && col == 0)) { // P4
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 255, 128, 0); // Orange                        
                    }
                    // React functions and hooks (P7, P8, P9, P5, P6)
                    else if ((row == 1 && col == 0) || // P7 (USE_CONTEXT)
                             (row == 1 && col == 1) || // P8 (REACT_FN_PROPS)
                             (row == 1 && col == 2) || // P9 (REACT_FN)
                             (row == 2 && col == 1) || // P5 (USE_EFFECT_HOOK)
                             (row == 2 && col == 2) || // P6 (USE_STATE)
                             (row == 0 && col == 2)) { // * (CN_LG)
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 0, 170, 255); // Light Blue
                    }
                    // Check if key is PENT or PPLS
                    else if ((row == 4 && col == 3) || // PENT
                             (row == 2 && col == 3)) { // PPLS
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 255, 0, 160); // Purple
                    }
                    else if((row==4 && col==1)) {
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 75, 0, 255); // Indigo/Blue-Purple
                    }
                    else if((row==4 && col==2)) {
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 180, 255, 0); // Lime
                    }
                    else if((row==0 && col==1)) {
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 255, 50, 0); // Orange
                    }
                    // Make numlock key purple
                    else if (row == 0 && col == 0) { // Numlock (TG(2))
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 255, 0, 255); // Purple
                    }
                    // Make minus key blue
                    else if (row == 0 && col == 3) { // Minus key (LT(1,KC_PMNS))
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 0, 0, 255); // Blue
                    }
                }
            }
            break;
        case 3:
            rgb_matrix_set_color_all(0, 0, 255); // Blue
            
            // Only color P1 and P2 keys
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    if ((row == 3 && col == 0) || // P1
                        (row == 3 && col == 1) || // P2
                        (row == 3 && col == 2)) { // P3
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 255, 0, 0); // Red
                    }
                    else if ((row == 2 && col == 1) || // PY_PRINT
                             (row == 2 && col == 2)) { // PY_TRY
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 0, 255, 0); // Green
                    }
                    else if ((row == 2 && col == 0) || // TF_INIT
                             (row == 1 && col == 0) || // TF_PLAN
                             (row == 1 && col == 1) || // TF_APPLY
                             (row == 1 && col == 2)) { // TF_DESTROY
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 255, 165, 0); // Orange
                    }
                    else if (row == 0 && col == 3) { // Minus key (LT(1,KC_PMNS))
                        rgb_matrix_set_color(g_led_config.matrix_co[row][col], 255, 0, 255); // Purple
                    }
                }
            }
            break;
    }
    return false;
}

// Macro implementations
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BUN_PRETTIER:
            if (record->event.pressed) {
                SEND_STRING("bun prettier . --write");
            }
            return false;
            
        case VERCEL_DEPLOY:
            if (record->event.pressed) {
                SEND_STRING("vercel deploy --prod");
            }
            return false;
            
        case ADD_JSDOC:
            if (record->event.pressed) {
                SEND_STRING("add good useful informative jsdoc for developers new to this codebase with explicit types, return and example");
            }
            return false;
            
        case ISSUE_FIX:
            if (record->event.pressed) {
                SEND_STRING("What is the following issue?  Describe it to me, and then fix it");
            }
            return false;
            
        case ISSUE_DESCRIBE:
            if (record->event.pressed) {
                SEND_STRING("Just describe the error here. Do not fix it, just describe it");
            }
            return false;
            
        case DEV_LOG:
            if (record->event.pressed) {
                // Create a new development log with formatting
                register_code(KC_LSFT);
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                unregister_code(KC_LSFT);
                
                SEND_STRING("add a Development Log here for [DATE AND TIME]");
                
                register_code(KC_LSFT);
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                unregister_code(KC_LSFT);
                
                SEND_STRING("[SHORT NOTE ON CHANGES MADE]");
                
                register_code(KC_LSFT);
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                unregister_code(KC_LSFT);
                
                SEND_STRING("CHANGES");
                
                register_code(KC_LSFT);
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                unregister_code(KC_LSFT);
                
                SEND_STRING("FILES ADDED");
                
                register_code(KC_LSFT);
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                unregister_code(KC_LSFT);
                
                SEND_STRING("Write the log in a codeblock so I can copy paste it");
            }
            return false;
            
        case PIP_INSTALL:
            if (record->event.pressed) {
                SEND_STRING("pip install");
            }
            return false;
            
        case PIP_FREEZE:
            if (record->event.pressed) {
                SEND_STRING("pip freeze > requirements.txt");
            }
            return false;
            
        case SP_FEYNCHAT:
            if (record->event.pressed) {
                // Open spotlight and search for feyn.chat
                register_code(KC_LGUI);
                register_code(KC_SPC);
                unregister_code(KC_SPC);
                unregister_code(KC_LGUI);
                
                wait_ms(100);
                SEND_STRING("feyn.chat");
                tap_code(KC_ENT);
            }
            return false;
            
        case SP_LOCALHOST:
            if (record->event.pressed) {
                // Open spotlight and search for localhost:3000
                register_code(KC_LGUI);
                register_code(KC_SPC);
                unregister_code(KC_SPC);
                unregister_code(KC_LGUI);
                
                wait_ms(100);
                SEND_STRING("localhost:3000");
                tap_code(KC_ENT);
            }
            return false;
        case REACT_FN:
            if (record->event.pressed) {
                SEND_STRING("export default function Potato() ");
                
                register_code(KC_LSFT);
                register_code(KC_LBRC);
                unregister_code(KC_LBRC);
                unregister_code(KC_LSFT);
                
                SEND_STRING("\n");
                tap_code(KC_ENT);
                SEND_STRING("return (\n<div> \n");
                tap_code(KC_ENT);
                SEND_STRING("</div>\n);");
            }
            return false;
        case REACT_FN_PROPS:
            if (record->event.pressed) {
                SEND_STRING("interface PotatoProps");
                
                register_code(KC_LSFT);
                register_code(KC_LBRC);
                unregister_code(KC_LBRC);
                unregister_code(KC_LSFT);
                
                SEND_STRING("\n");
                tap_code(KC_ENT);
                tap_code(KC_DOWN);
                tap_code(KC_ENT);
                
                SEND_STRING("\nexport default function Potato(");
                
                register_code(KC_LSFT);
                register_code(KC_LBRC);
                unregister_code(KC_LBRC);
                unregister_code(KC_LSFT);
                
                SEND_STRING(" ");
                
                register_code(KC_LSFT);
                register_code(KC_RBRC);
                unregister_code(KC_RBRC);
                unregister_code(KC_LSFT);
                
                SEND_STRING(": PotatoProps) ");
                
                register_code(KC_LSFT);
                register_code(KC_LBRC);
                unregister_code(KC_LBRC);
                unregister_code(KC_LSFT);
                
                SEND_STRING("\n");
                tap_code(KC_ENT);
                SEND_STRING("\treturn (\n<div>\n");
                tap_code(KC_ENT);
                SEND_STRING("</div>\n);");
                tap_code(KC_ENT);
                
                register_code(KC_LSFT);
                register_code(KC_RBRC);
                unregister_code(KC_RBRC);
                unregister_code(KC_LSFT);
            }
            return false;
        case USE_STATE:
            if (record->event.pressed) {
                SEND_STRING("const [setStateName, setStateValue] = useState(initialStateValue);");
            }
            return false;
        case USE_EFFECT_HOOK:
            if (record->event.pressed) {
                // Output the entire useEffect as a single line
                SEND_STRING("useEffect(() => { /* Effect code here */ return () => { /* Cleanup code here */ }; }, []); // Dependencies array");
                
                // Select the line (optional if your editor keeps it selected by default)
                register_code(KC_HOME);
                unregister_code(KC_HOME);
                register_code(KC_LSFT);
                register_code(KC_END);
                unregister_code(KC_END);
                unregister_code(KC_LSFT);
                
                // Format with Cmd+R, F (Format selection)
                register_code(KC_LGUI);
                register_code(KC_R);
                register_code(KC_F);
                unregister_code(KC_F);
                unregister_code(KC_R);
                unregister_code(KC_LGUI);
                
                wait_ms(50); // Brief delay
            }
            return false;
        case USE_CONTEXT:
            if (record->event.pressed) {
                SEND_STRING("const contextValue = useContext(MyContext);");
            }
            return false;
        case PIP_REQ:
            if (record->event.pressed) {
                SEND_STRING("pip install -r requirements.txt");
            }
            return false;
        case PY_TRY:
            if (record->event.pressed) {
                SEND_STRING("try: \n\t# code here\nexcept Exception as e: \n\tprint(e)");
            }
            return false;
        case PY_PRINT:
            if (record->event.pressed) {
                SEND_STRING("print('')");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            return false;
        case TF_INIT:
            if (record->event.pressed) {
                SEND_STRING("make init");
            }
            return false;
        case TF_PLAN:
            if (record->event.pressed) {
                SEND_STRING("make plan");
            }
            return false;
        case TF_APPLY:
            if (record->event.pressed) {
                SEND_STRING("make apply");
            }
            return false;
        case TF_DESTROY:
            if (record->event.pressed) {
                SEND_STRING("make destroy");
            }
            return false;
        case CN_LG:
            if (record->event.pressed) {
                SEND_STRING("console.log('')");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            return false;
        case FRMT_JS:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_A);
                unregister_code(KC_A);
                unregister_code(KC_LGUI);
                register_code(KC_LGUI);
                register_code(KC_R);
                register_code(KC_F);
                unregister_code(KC_F);
                unregister_code(KC_R);
                unregister_code(KC_LGUI);
            }
            return false;
    }
    return true;
}

