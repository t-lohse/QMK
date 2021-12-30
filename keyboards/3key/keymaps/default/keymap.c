#include "3key.h"

#define NORMAL 18  //Orange (StackOverflow)
#define RED 0
#define GREEN 85
#define BLUE 169

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
    /*
    switch (keycode) {
        case KC_1:
            if (record->event.pressed) {
                rgblight_sethsv(RED, 255, 255);
            } else {
                rgblight_sethsv(NORMAL, 255, 255);
            }
            return false;
        case KC_2:
            if (record->event.pressed) {
                rgblight_sethsv(GREEN, 255, 255);
            } else {
                rgblight_sethsv(NORMAL, 255, 255);
            }
            return false;
        case KC_3:
            if (record->event.pressed) {
                rgblight_sethsv(BLUE, 255, 255);
            } else {
                rgblight_sethsv(NORMAL, 255, 255);
            }
            return false;
    }
    */
    switch (record->event.key.col) {
        case 0:
            if (record->event.pressed) {
                rgblight_sethsv(RED, 255, 255);
            } else {
                rgblight_sethsv(NORMAL, 255, 255);
            }
            break;
        case 1:
            if (record->event.pressed) {
                rgblight_sethsv(GREEN, 255, 255);
            } else {
                rgblight_sethsv(NORMAL, 255, 255);
            }
            break;
        case 2:
            if (record->event.pressed) {
                rgblight_sethsv(BLUE, 255, 255);
            } else {
                rgblight_sethsv(NORMAL, 255, 255);
            }
            break;
    }

	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}
    
}
