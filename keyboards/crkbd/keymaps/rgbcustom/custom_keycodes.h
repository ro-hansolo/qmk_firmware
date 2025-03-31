#pragma once

#include QMK_KEYBOARD_H

// Custom macro keycodes
enum custom_keycodes {
    BUN_DEV = QK_USER,  // "bun dev"
    BUN_PRETTIER,       // "bun prettier . --write"
    VERCEL_DEPLOY,      // "vercel deploy --prod"
    BUN_LINT,           // "bun lint"
    SP_CURSOR,          // Spotlight + "cursor"
    SP_SAFARI,          // Spotlight + "safari"
    SP_GITHUB,          // Spotlight + "github desktop"
    SP_TERMINAL,        // Spotlight + "terminal"
    SP_WHATSAPP,        // Spotlight + "whatsapp"
    SP_SETTINGS,        // Spotlight + "system settings"
    SP_MAIL,            // Spotlight + "mail"
    SP_MUSIC,           // Spotlight + "apple music"
    SP_REDDIT,          // Spotlight + "reddit"
    SP_YOUTUBE,         // Spotlight + "youtube"
    SP_MESSAGES,         // Spotlight + "messages"
    SP_MOTORSPORT,      // Spotlight + "motorsport.com"
    SP_LOCALHOST,       // Spotlight + "localhost:3000"
    SP_FEYNCHAT,        // Spotlight + "feynchat"
    SP_PASSWORD_MANAGER, // Spotlight + "passwords"
};