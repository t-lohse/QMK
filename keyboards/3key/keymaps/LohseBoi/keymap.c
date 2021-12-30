#include "3key.h"

#define NORMAL 18  //Orange (StackOverflow)
#define RED 0
#define GREEN 85
#define BLUE 169

#define ASCII_CODE
uint8_t asciiChar = 0;
uint8_t asciiCounter = 0;

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

#ifdef ASCII_CODE
    switch (record->event.key.col) {
        case 0:  // Left
            if (!record->event.pressed) {
                asciiChar <<= 1;
                asciiChar += 1;
                asciiCounter++;
            } 
            break;
        case 1:  // Center
            if (!record->event.pressed) {
                char str[2] = {' ', 0};
                sprintf(str, "%c", asciiChar);
                send_string(str);
                asciiChar = 0;
                asciiCounter = 0;
            } 
            break;
        case 2: // Right
            if (!record->event.pressed) {
                asciiChar <<= 1;
                asciiChar += 0;
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
