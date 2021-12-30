/* Copyright 2015-2021 Jack Humbert
 *
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
#include "muse.h"

//Lower hold/tap
uint16_t lwr_timer = 0;
bool lwr_tapped = false;
//Raise hold/tap
uint16_t rse_timer = 0;
bool rse_tapped = false;

//Shift/Caps
#define KC_SFTCL MT(MOD_LSFT, KC_CAPS)

//Alt+Tab
#define ALT_TAB KC_ALT_TAB
bool alttab_active = false;

//Media macro variables
const uint16_t media_time = 750;
bool is_media_active = false;
uint16_t media_timer = 0;
uint8_t media_counter = 0;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,

  //Homemade Keys
  KC_HLWR,
  KC_HRWR,
  KC_MED,
  KC_ALT_TAB,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty                                    |
 * ,-----------------------------------------------------------------------------------.
 * |  -   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ESC/` |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SHIFT |   [  | Ctrl | GUI  | LWR  | SPC  |  ENT | RSE  | LAlt |  DEL |   ]  | BSPC |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_MINS,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
    KC_GESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSLS,
    KC_TAB,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
    KC_LSFT,  KC_LBRC, KC_LCTL, KC_LGUI, KC_HLWR, KC_SPC,  KC_ENT,  KC_HRWR, KC_LALT, KC_DEL,  KC_RBRC, KC_BSPC
),

/* Lower                                     |
 * ,-----------------------------------------------------------------------------------.
 * |   -  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  `   |MEDIA | VOLU |      |      |      | LEFT | DOWN |  UP  | RIGHT|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ALTTAB| MUTE | VOLD |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SFT/CL|      | CTRL | GUI  | LWR  | SPC  | ENT  | RSE  | LALT | DEL  |      | BCSP |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_MINS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
    KC_GRV,   KC_MED,  KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    ALT_TAB,  KC_MUTE, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_SFTCL, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______
),

/* Raise                                     |
 * ,-----------------------------------------------------------------------------------.
 * |      |      |   Å  |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  ~   |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |   Ø  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |  Æ   |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SHIFT |      | CTRL | GUI  | LWR  | SPC  | ENT  | RSE  | LALT | DEL  |      | BCSP |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX,    RALT(KC_W), XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
    KC_TILD, XXXXXXX,    KC_F1,      KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   XXXXXXX, RALT(KC_L), XXXXXXX, XXXXXXX,
    _______, RALT(KC_Z), KC_F7,      KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
    _______, XXXXXXX,    _______,    _______, _______,  _______, _______, _______, _______, _______,    XXXXXXX, _______
),


/* Adjust (Lower + Raise)                    |
 * ,-----------------------------------------------------------------------------------.
 * |      |QWERTY|      |      |      |      |      |      |      |EEPRST| DEBUG| RESET|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | LWR  | SPC  | ENT  | RSE  |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    XXXXXXX, QWERTY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST, DEBUG,   RESET,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        //print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
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
    case KC_HRWR:
        if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            rse_timer = timer_read();

        } else {
            if (timer_elapsed(rse_timer) < 100) {
                rse_tapped = !rse_tapped;
                rse_tapped ? layer_on(_RAISE) : layer_off(_RAISE);
            } else {
                layer_off(_RAISE);
            }

            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            #ifdef AUDIO_ENABLE
            static bool play_sound = false;
            #endif
            if (active) {
                #ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
                #endif
                layer_on(_ADJUST);
            } else {
                #ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
                #endif
                layer_off(_ADJUST);
            }
            #ifdef AUDIO_ENABLE
            play_sound = true;
            #endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
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

    #ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
    #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
