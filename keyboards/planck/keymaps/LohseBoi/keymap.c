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
#include "../../../tlohse.h"

MACRO_VARS

enum planck_layers {
    _DVORAK,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

KEYCODES(planck_keycodes, BACKLIT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK] = t_DVORAK,
    [_QWERTY] = t_QWERTY,
    [_LOWER] = t_LOWER,
    [_RAISE] = t_RAISE,
    [_ADJUST] = t_ADJUST,
};


#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

int kc;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case QWERTY:
          if (record->event.pressed) {
              set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
      case DVORAK:
          if (record->event.pressed) {
              set_single_persistent_default_layer(_DVORAK);
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
    PROCESS_CUSTOM
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
