#include "3key.h"

#define NORMAL 18  //Orange (StackOverflow)
#define RED 0
#define GREEN 85
#define BLUE 169

#define ASCII_WRITER
#ifdef ASCII_WRITER
uint8_t asciiChar = 0;
uint8_t asciiCounter = 0;

uint16_t asciiTimer = 0;
uint16_t asciiLimit = 200;

uint8_t asciiClick = 0;
bool asciiHolding = false;
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT(KC_1, KC_2, KC_3)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	keyevent_t event = record->event;

	switch (event.pressed) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
#ifdef ASCII_WRITER
    if (asciiClick > 0) {
        if (timer_elapsed(asciiTimer) >= asciiLimit) {
            if (asciiClick == 1) { //Single-tap to send, Double-click to empty buffer only
                char str[2] = {' ', 0};
                sprintf(str, "%c", asciiChar);
                send_string(str);
            }
            asciiChar = 0;
            asciiCounter = 0;
            asciiClick = 0;
            asciiTimer = timer_read();
        }
    } else if (asciiHolding) {
        if (timer_elapsed(asciiTimer) >= asciiLimit/4) {
            register_code(KC_BSPC);
            asciiHolding = false;
        }
    }
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (record->event.key.col) {
        case 0:  // Left
            if (record->event.pressed) {
                rgblight_sethsv(BLUE, 255, 255);
            } else {
                rgblight_sethsv(NORMAL, 255, 255);
            }
            break;
        case 1:  // Center
            if (record->event.pressed) {
                rgblight_sethsv(GREEN, 255, 255);
            } else {
                rgblight_sethsv(NORMAL, 255, 255);
            }
            break;
        case 2: // Right
            if (record->event.pressed) {
                rgblight_sethsv(RED, 255, 255);
            } else {
                rgblight_sethsv(NORMAL, 255, 255);
            }
            break;
    }

#ifdef ASCII_WRITER
    switch (record->event.key.col) {
        case 0:  // Left
            if (!record->event.pressed) {
                asciiChar <<= 1;
                asciiChar += 1;
                asciiCounter++;
            } 
            break;
        case 1:  // Center
            if (record->event.pressed) { //Press
                asciiClick++;
                asciiHolding = true;
                asciiTimer = timer_read();
            } else { //Release
                unregister_code(KC_BSPC);
                asciiHolding = false;
            } 
            break;
        case 2: // Right
            if (!record->event.pressed) {
                asciiChar <<= 1;
                asciiCounter++;
            } 
            break;
    }
    if (asciiCounter >= 8) {
        char str[2] = {' ', 0};
        sprintf(str, "%c", asciiChar);
        send_string(str);
        asciiChar = 0;
        asciiCounter = 0;
    }

    return false;
#endif

	return true;
}
