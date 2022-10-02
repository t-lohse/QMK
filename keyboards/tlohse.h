/* Dvorak                                    |
 * ,-----------------------------------------------------------------------------------.
 * |  _   |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ESC/` |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SHIFT | LAlt | Ctrl | GUI  | LWR  | SPC  |  ENT | RSE  |AltGr |  DEL |PrtScr| BSPC |
 * `-----------------------------------------------------------------------------------'
 */
#define t_DVORAK LAYOUT_ortho_4x12( \
    KC_UNDM,  KC_QUOOT,KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_EQL, \
    KC_GESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,  KC_SLSH, \
    KC_TAB,   KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,  KC_BSLS, \
    KC_LSFT,  KC_LALT, KC_LCTL, KC_LGUI, KC_LWR, KC_SPC,  KC_ENT,  KC_RWR, KC_RALT, KC_DEL,  KC_PSCR, KC_BSPC \
)

/* Qwerty                                    |
 * ,-----------------------------------------------------------------------------------.
 * |  _   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ESC/` |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SHIFT | LAlt | Ctrl | GUI  | LWR  | SPC  |  ENT | RSE  |AltGr |  DEL |PrtScr| BSPC |
 * `-----------------------------------------------------------------------------------'
 */
#define t_QWERTY LAYOUT_ortho_4x12( \
    KC_UNDM,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL, \
    KC_GESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSLS, \
    KC_TAB,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOOT, \
    KC_LSFT,  KC_LALT, KC_LCTL, KC_LGUI, KC_LWR, KC_SPC,  KC_ENT,  KC_RWR, KC_RALT, KC_DEL,  KC_PSCR, KC_BSPC \
)

/* Lower                                     |
 * ,-----------------------------------------------------------------------------------.
 * |   -  |  {   |   (  |   &  |   !  |  #   |   ^  |   %  |   *  |   )  |   }  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  `   |  [   |   ,  |   .  |   @  |  $   | LEFT | DOWN |  UP  | RIGHT|   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |  ;/Z |      |      |      |      | VOLD | VOLU | BRID | BRIU | MUTE |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SFT/CL| Alt  | CTRL | GUI  | LWR  | SPC  | ENT  | RSE  |AltGr | DEL  |PrtScr| BCSP |
 * `-----------------------------------------------------------------------------------'
 */
#define t_LOWER LAYOUT_ortho_4x12( \
    KC_MINS,  KC_LCBR, KC_LPRN, KC_AMPR, KC_EXLM, KC_HASH, KC_CIRC, KC_PERC, KC_ASTR, KC_RPRN, KC_RCBR, KC_PLUS, \
    KC_GRV,   KC_LBRC, KC_COMM, KC_DOT, KC_AT, KC_DLR, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RBRC, _______, \
    KC_TAB,   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, KC_MUTE, _______, \
    KC_SFTCL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)

/* Raise                                     |
 * ,-----------------------------------------------------------------------------------.
 * |   -  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  | Prev | PLYP | Next |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SFT  | Alt  | CTRL | GUI  | LWR  | SPC  | ENT  | RSE  |AltGr | DEL  |PrtScr| BCSP |
 * `-----------------------------------------------------------------------------------'
 */
#define t_RAISE LAYOUT_ortho_4x12( \
    KC_MINS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PLUS, \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
    _______, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SOUND, KC_SOUNDF, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)


/* Adjust (Lower + Raise)                    |
 * ,-----------------------------------------------------------------------------------.
 * |      |DVORAK|QWERTY|      |      |      |      |      |      |EEPRST| DEBUG| RESET|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | LWR  | SPC  | ENT  | RSE  |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
#define t_ADJUST LAYOUT_ortho_4x12( \
    XXXXXXX, DVORAK,  QWERTY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST, DEBUG,   RESET, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
)

//Shift/Caps
#define KC_SFTCL MT(MOD_LSFT, KC_CAPS)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define KEYCODES(board, special) enum board { \
    DVORAK = SAFE_RANGE, \
    QWERTY, \
    special, \
    \
    KC_HLWR, \
    KC_HRWR, \
    KC_LWR, \
    KC_RWR, \
    KC_SOUND, \
    KC_SOUNDF, \
    KC_QUOOT, \
    KC_UNDM, \
};

//Lower/Raise hold/tap
#define MACRO_VARS uint16_t lwr_timer = 0; \
bool lwr_tapped = false; \
uint16_t rse_timer = 0; \
bool rse_tapped = false;

bool homemade_keys(uint16_t keycode, keyrecord_t *record);

#define PROCESS_CUSTOM                                                      \
    case KC_HLWR:                                                           \
        if (record->event.pressed) {                                        \
            layer_on(_LOWER);                                               \
            update_tri_layer(_LOWER, _RAISE, _ADJUST);                      \
            lwr_timer = timer_read();                                       \
                                                                            \
        } else {                                                            \
            if (timer_elapsed(lwr_timer) < 100) {                           \
                lwr_tapped = !lwr_tapped;                                   \
                lwr_tapped ? layer_on(_LOWER) : layer_off(_LOWER);          \
            } else {                                                        \
                layer_off(_LOWER);                                          \
            }                                                               \
            layer_off(_LOWER);                                              \
            update_tri_layer(_LOWER, _RAISE, _ADJUST);                      \
            unregister_code(KC_LALT);                                       \
        }                                                                   \
        return false;                                                       \
    case KC_HRWR:                                                           \
        if (record->event.pressed) {                                        \
            layer_on(_RAISE);                                               \
            update_tri_layer(_LOWER, _RAISE, _ADJUST);                      \
            rse_timer = timer_read();                                       \
                                                                            \
        } else {                                                            \
            if (timer_elapsed(rse_timer) < 100) {                           \
                rse_tapped = !rse_tapped;                                   \
                rse_tapped ? layer_on(_RAISE) : layer_off(_RAISE);          \
            } else {                                                        \
                layer_off(_RAISE);                                          \
            }                                                               \
            update_tri_layer(_LOWER, _RAISE, _ADJUST);                      \
        }                                                                   \
        return false;                                                       \
    case KC_LWR:                                                            \
        if (record->event.pressed) {                                        \
            layer_on(_LOWER);                                               \
            update_tri_layer(_LOWER, _RAISE, _ADJUST);                      \
                                                                            \
        } else {                                                            \
            layer_off(_LOWER);                                              \
            update_tri_layer(_LOWER, _RAISE, _ADJUST);                      \
            unregister_code(KC_LALT);                                       \
        }                                                                   \
        return false;                                                       \
    case KC_RWR:                                                            \
        if (record->event.pressed) {                                        \
            layer_on(_RAISE);                                               \
            update_tri_layer(_LOWER, _RAISE, _ADJUST);                      \
                                                                            \
        } else {                                                            \
            layer_off(_RAISE);                                              \
            update_tri_layer(_LOWER, _RAISE, _ADJUST);                      \
        }                                                                   \
        return false;                                                       \
    case KC_SOUND:                                                          \
        if (record->event.pressed) {                                        \
            audio_play_tone(NOTE_C4);                                       \
        } else {                                                            \
            audio_stop_tone(NOTE_C4);                                       \
        }                                                                   \
        return false;                                                       \
    case KC_SOUNDF:                                                         \
        if (record->event.pressed) {                                        \
            audio_play_tone(NOTE_CS4);                                      \
        } else {                                                            \
            audio_stop_tone(NOTE_CS4);                                      \
        }                                                                   \
        return false;                                                       \
    case KC_QUOOT:                                                          \
        if (record->event.pressed) {                                        \
            if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {      \
                unregister_code(KC_LSFT);                                   \
                register_code(KC_QUOT);                                     \
                register_code(KC_LSFT);                                     \
            } else {                                                        \
                register_code16(KC_DQT);                                    \
            }                                                               \
        } else {                                                            \
            unregister_code16(KC_DQT);                                      \
            unregister_code(KC_QUOT);                                       \
        }                                                                   \
        return false;                                                       \
    case KC_UNDM:                                                           \
        if (record->event.pressed) {                                        \
            if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {      \
                unregister_code(KC_LSFT);                                   \
                register_code(KC_MINS);                                     \
                register_code(KC_LSFT);                                     \
            } else {                                                        \
                register_code16(KC_UNDS);                                   \
            }                                                               \
        } else {                                                            \
            unregister_code16(KC_UNDS);                                     \
            unregister_code(KC_MINS);                                       \
        }                                                                   \
        return false;                    
