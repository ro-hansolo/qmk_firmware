#pragma once

#include QMK_KEYBOARD_H

// Layer definitions
enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};

// Custom macro keycodes
enum custom_keycodes {
    MAC_CMDK = QK_USER, // Cmd+K       (Cursor Inline Editor)
    MAC_CMDL,           // Cmd+L       (Cursor Add to Chat)
    MAC_CSSL,           // Cmd+Shift+L (Cursor New Chat)
    MAC_CSCA,           // Cmd+Shift+5 (screen capture)
    MAC_CMDB,           // Cmd+B       (VSCODE PANEL)
    MAC_CMDJ,           // Cmd+J       (VSCODE TERMINAL)
    BUN_DEV,            // "bun dev"
    BUN_LINT,           // "bun lint"
    SP_CURSOR,          // Spotlight + "cursor"
    SP_SAFARI,          // Spotlight + "safari"
    SP_GITHUB,          // Spotlight + "github desktop"
    SP_TERMINAL,        // Spotlight + "terminal"
    SP_WHATSAPP,        // Spotlight + "whatsapp"
    SP_SETTINGS,        // Spotlight + "system settings"
    SP_MAIL,            // Spotlight + "mail"
};