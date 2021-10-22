//#include <stdio.h>
#include QMK_KEYBOARD_H

//WPM
static void to_string(char*, uint8_t);
uint16_t wpm_timer = 0;

//Shift/Caps
#define KC_SFTCL MT(MOD_LSFT, KC_CAPS)

//Alt+Tab
#define ALT_TAB KC_ALT_TAB
bool alttab_active = false;

//Lower hold/tap
uint16_t lwr_timer = 0;
bool lwr_tapped = false;

//Media macro variables
const uint16_t media_time = 750;
bool is_media_active = false;
uint16_t media_timer = 0;
uint8_t media_counter = 0;

//Encoder turning counter
uint8_t turner[2] = {0, 0};

/*  TODO
 *      _LOWER
 *      _RAISE
 *      _ADJUST
 *      _GAMER
 *      Perhaps arrow layer (WASD and HJKL) for dual play (Encoders could be directions as well - R: W/S, L: UP/DOWN - for pingpong and shit)
 *      More macros
 *      Secondary Screen Info - Ideas:
 *          - Date?
 *          - Time?
 *          - Noted cmd for bad memory (IE Server)
 */


/*  Potential macros:
 *      Ctrl+F and use encoder to scroll through (print search status on oled)
 *      PrintScreen (Screenshot)
 */


enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _GAMER,

    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_GAMER, //Homemade

    //Homemade keycodes
    KC_MED,
    KC_ALT_TAB,
    KC_HLWR,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY (DONE) - TG(layer) for toggle --- lctrl and win/super is switch cuz error I guess
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   -  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   =  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC/`|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  TAB |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------| MUTE  |    | Media |------+------+------+------+------+------|
 * |LSHIFT|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | BSPC |
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *            |  [   | LCTRL| WIN/ |LOWER/| / Space /      \ Enter \  | RAISE| Lalt | Del  |   ]  |
 *            |      |      | SUPER|  FN  |/       /        \       \ |      |      |      |      |
 *            `-----------------------------------'          '-------`'---------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_MINS,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL,  \
  KC_GESC,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS, \
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    KC_MED,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_BSPC, \
                 KC_LBRC, KC_LCTL, KC_LGUI, KC_HLWR, KC_SPC,      KC_ENT,  KC_RAISE, KC_LALT, KC_DEL, KC_RBRC \
),

/* RAISE (NOT DONE - Macros like Alt+F4, and such)
 * ,-----------------------------------------.                    ,----------------------------------------.
 * |   -  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   =  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |      |  Å   |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |      |      |      |      |      |-------.    ,-------|      |      |      |   Ø  |      |      |
 * |------+------+------+------+------+------| MUTE  |    | Media |------+------+------+------+------+------|
 * |SHIFT |  Æ   |      |      |      |      |-------|    |-------|      |      |      |      |      | BSPC |
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *            |      | LCTRL| WIN/ |LOWER/| / Space /      \ Enter \  | RAISE| Lalt | Del  |      |
 *            |      |      | SUPER|  FN  |/       /        \       \ |      |      |      |      |
 *            `-----------------------------------'          '-------`'---------------------------'
 */
[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,   \
  KC_GRAVE, XXXXXXX, RALT(KC_W), XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, RALT(KC_L), XXXXXXX, XXXXXXX, \
  KC_LSFT, RALT(KC_Z), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, \

                    XXXXXXX, _______, _______, _______, _______,           _______, _______, _______, _______, XXXXXXX \
),

/* LOWER (NOT DONE - fn, PgUp/Down, etc.)
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |ALTTAB|      |      |      |      |      |-------.    ,-------| Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------| MUTE  |    | Media |------+------+------+------+------+------|
 * | S/CL |      |      |      |      |      |-------|    |-------|      ||     |      |      |      | BSPC |
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *            |      | LCTRL| WIN/ |LOWER/| / Space /      \ Enter \  | RAISE| Lalt | Del  |      |
 *            |      |      | SUPER|  FN  |/       /        \       \ |      |      |      |      |
 *            `-----------------------------------'          '-------`'---------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,                           KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,   \
  KC_GRAVE, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  ALT_TAB,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  XXXXXXX, XXXXXXX, \
  KC_SFTCL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
                     XXXXXXX, _______, _______, _______, _______,       _______, _______, _______, _______, XXXXXXX \
),

/* ADJUST (NOT DONE - perhaps macros)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      | RESET|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |QWERTY|      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MACWIN|      |      |GAMER |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |SHIFT |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      | BSPC |
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *            |      | LCTRL| WIN/ |LOWER/| / Space /      \ Enter \  | RAISE| Ralt | Del  |      |
 *            |      |      | SUPER|  FN  |/       /        \       \ |      |      |      |      |
 *            `-----------------------------------'          '-------`'---------------------------'
 */
[_ADJUST] = LAYOUT( \
  XXXXXXX , XXXXXXX,  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET, \
  XXXXXXX , KC_QWERTY,XXXXXXX, XXXXXXX ,XXXXXXX,XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX , XXXXXXX,CG_TOGG, XXXXXXX,    XXXXXXX,  KC_GAMER,                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, \
  _______ , XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, _______, \
                   XXXXXXX, _______, _______, _______, _______,     _______, _______, _______, _______, XXXXXXX \
),

/*
 * GAMER (NOT DONE)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   =  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------| MUTE  |    | Media |------+------+------+------+------+------|
 * |LSHIFT|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | BSPC |
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *            |LOWER |I(nv) |M(ap) | ALT  | / Space /      \ Enter \  | RAISE| Ralt | Del  |ADJUST|
 *            |      |      |      |      |/       /        \       \ |      |      |      |      |
 *            `-----------------------------------'          '-------`'---------------------------'
 */
[_GAMER] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL,  \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    KC_MED, KC_N,    KC_M,    KC_COMM,   KC_DOT, KC_SLSH, KC_BSPC, \
                      KC_LOWER, KC_I, KC_M, KC_LALT, _______,    _______, KC_RAISE, KC_LALT, KC_DELETE, KC_ADJUST \
  )
};

//#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    /*
    static const char PROGMEM logo[] = {  //archHub
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfe, 
        0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
        0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
        0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
        0xfe, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0xc0, 0xf8, 0x1c, 0x1c, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xc0, 0xc0, 0x80, 0x80, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x40, 0xc0, 0x00, 
        0x00, 0x00, 0xfe, 0xfe, 0x80, 0xc0, 0x40, 0x40, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0xff, 0xff, 0x01, 
        0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x21, 0x21, 0xf3, 0xff, 0xff, 0x3f, 0x3f, 
        0x3f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 
        0xff, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xbf, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0xbf, 
        0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0xc0, 0xf8, 0x3f, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x3f, 0xf8, 0xc0, 0x00, 0x00, 0x00, 
        0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0xe1, 0xc0, 0xc0, 0x80, 0xc0, 0x00, 
        0x00, 0x00, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 
        0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0xfe, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x80, 0x00, 0x1f, 0x3f, 0x3f, 
        0x3f, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x3f, 0x0c, 0x80, 0xe1, 0xe1, 0x80, 0x0c, 0x3f, 0x7f, 
        0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0x7f, 
        0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
        0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
        0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
        0x7f, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
    };
    oled_write_raw_P(logo, sizeof(logo));
    */
    
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR(" WPM"), false);
    //oled_write_ln_P(PSTR("NUM\n"), true); //True, when WPM is above a certain range
    char str[7] = {' ', ' ', ' ', ' ', ' ', '\n', 0};
    uint8_t wpm = get_current_wpm();
    to_string(str+1, wpm);
    oled_write_ln(str, wpm > 69);
    oled_write_ln_P(PSTR("More\nShit\n1234567890"), false);
    if (wpm == 0 && wpm_timer == 0 && is_oled_on())
        wpm_timer = timer_read();
    else if (wpm > 0)
        wpm_timer = 0;
    else if (timer_elapsed(wpm_timer) >= OLED_TIMEOUT) {
        oled_off();
        wpm_timer = 0;
    }
}

static void to_string(char* str, uint8_t num) {
    bool prev = false;
    if (num >= 100) {
        *str = ((num - (num % 100)) / 100) + 48;
        str = str+1;
        num = num % 100;
        prev = true;
    }

    if (num >= 10) {
        *str = ((num - (num % 10)) / 10) + 48;
        str = str+1;
        num = num % 10;
        prev = true;
    }
    else if (prev == true) {
        *str = '0';
        str = str+1;
    }

    *str = num + 48;
    //*(str+1) = '\n';
    //*(str+2) = 0;

}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("MAC"), false);
    } else {
        oled_write_ln_P(PSTR("WIN"), false);
    }

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt\n"), false);
            break;
        case _GAMER:
            oled_write_ln_P(PSTR("GAMER"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case _GAMER:
            oled_write_P(PSTR("GAMER\n"), false);
            break;

        case _RAISE:
            oled_write_P(PSTR("RSE\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LWR\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n"), false);
    }
    oled_write_P(PSTR("\n\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    //if (is_keyboard_master()) {
      //  return OLED_ROTATION_270;
    //}

    return OLED_ROTATION_270;
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

//#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    oled_on();
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_GAMER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAMER);
            }
            return false;
       
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                unregister_code(KC_LALT);
                //alttab_active = false;
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_MED:
            if (record->event.pressed) {
                if (!is_media_active)
                    media_timer = timer_read(); //Timer starts
        
                is_media_active = true; 
                media_counter++;
            } else {
                //Do nothing on release
            }
            break;
        case KC_ALT_TAB:
            if (record->event.pressed) {
                //alttab_active = true;
                register_code(KC_LALT);
                SEND_STRING(SS_TAP(X_TAB));
            } else {
                //Do nothing on release
            }
            return false;
        case KC_HLWR:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                lwr_timer = timer_read();

            } else {
                if (timer_elapsed(lwr_timer) < 100) {
                    lwr_tapped = !lwr_tapped;
                    lwr_tapped ? layer_on(_LOWER) : layer_off(_LOWER);
                } else {
                    layer_off(_LOWER);
                }

                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                unregister_code(KC_LALT);
            }
            return false;
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_media_active) {  //If the media key has been pressed
        if (timer_elapsed(media_timer) > media_time) {  //If the time is up
            
            switch (media_counter) {  //Number of times pressed in given timeframe
                case 1:
                    SEND_STRING(SS_TAP(X_MPLY));  //Play/Pause
                    break;
                case 2:
                    SEND_STRING(SS_TAP(X_MNXT));  //Next track
                    break;
                case 3: default:
                    SEND_STRING(SS_TAP(X_MPRV));  //Previous track
                    break;
            }
            //Resets variables
            media_counter = 0;
            is_media_active = false;
        }
    }
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    clockwise = !clockwise;
    if (index == 0) { //left encoder
        if (turner[index] == 1) {
            if (clockwise)
                tap_code(KC_BRIU);
                //tap_code(KC_WH_D);  //Mouse wheel - Scroll (WORKING)
            else
                tap_code(KC_BRID);
                //tap_code(KC_WH_U);
        }
    } else if (index == 1) { //right encoder
        if (turner[index] == 1) {
            if (clockwise)
                tap_code(KC_VOLU);  //Volume
            else
                tap_code(KC_VOLD);
        }
    }
    turner[index] = turner[index] == 1 ? 0 : 1;
    return true;
}

#endif
