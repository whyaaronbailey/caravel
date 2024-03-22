// Copyright 2024 Kamran Shah (@whyaaronbailey)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "print.h"

enum custom_keycodes {
    COPYACC = SAFE_RANGE,
    OPENGE,
    OPENEPIC,
    PASTE,
    DICTATE,
	WL_SOFTTISSUE,
	WL_BONE,
	WL_BRAIN,
	WL_STROKE,
	WL_LUNG,
	WL_VASCULAR,
	WL_HARDWARE,
	ARROW,
	ZOOM,
	MEASURE,
	SCROLLUP,
	SCROLLDOWN,
	WHEELUP,
	WHEELDOWN,
	SPINE_C,
	SPINE_T,
	SPINE_L,
	NEXTFIELD,
	DELETE,
	ANNOTATIONS,
	PREVFIELD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        WL_SOFTTISSUE,  
        WL_STROKE, 
        WL_LUNG,
        ANNOTATIONS,  
        ZOOM, 
        WL_BONE,  
        WL_BRAIN, 
        SCROLLUP,  
        OPENEPIC,  
        ARROW, 
        SPINE_L, 
        KC_MS_WH_UP,  
        KC_MS_WH_DOWN, 
        SCROLLDOWN, 
        MEASURE, 
        COPYACC,  
        OPENGE,  
        SPINE_C,  
        SPINE_L, 
        SPINE_T,  
        MO(1),   
        DICTATE, 
        DELETE, 
        NEXTFIELD
    ),
    [1] = LAYOUT(
        KC_4,
		KC_6,
		KC_5,
		KC_GRV,
		KC_PGUP, 
		KC_HOME, 
		KC_END,  
		KC_UP,   
		LSFT(KC_TAB), 
		KC_PGDN, 
		_______, 
		KC_LEFT, 
		KC_RGHT, 
		KC_DOWN, 
		QK_BOOT, 
		_______, 
		_______, 
		KC_7,    
		KC_9,    
		KC_8,    
		_______, 
		_______, 
		_______, 
		_______
    )
};
void send_bytes_26_to_34(void) {
    uint8_t data[9] = {0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    raw_hid_send(data, sizeof(data));
}

static deferred_token token = INVALID_DEFERRED_TOKEN;  // For SCROLLUP.

void pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) { // If any key is pressed, check if scrolling is active and stop.
        if (token) {
            cancel_deferred_exec(token);
            token = INVALID_DEFERRED_TOKEN;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SCROLLUP: { // Mouse wheel up with constant repeating.
            if (record->event.pressed) { // Mouse wheel up action started or stopped.
                if (token) { // If already repeating, stop.
                    cancel_deferred_exec(token);
                    token = INVALID_DEFERRED_TOKEN;
                } else { // If not repeating, start.
                    tap_code(KC_MS_WH_UP); // Initial action of mouse wheel up.
                    uint32_t wh_up_callback(uint32_t trigger_time, void* cb_arg) {
                        tap_code(KC_MS_WH_UP);
                        return REP_DELAY_MS; // Return constant delay for SCROLLUP.
                    }
                    token = defer_exec(REP_DELAY_MS, wh_up_callback, NULL); 
                }
            }
        } return false; // Skip normal handling.

        case SCROLLDOWN: { // Mouse wheel down with constant repeating.
            if (record->event.pressed) { // Mouse wheel down action started or stopped.
                if (token) { // If already repeating, stop.
                    cancel_deferred_exec(token);
                    token = INVALID_DEFERRED_TOKEN;
                } else { // If not repeating, start.
                    tap_code(KC_MS_WH_DOWN); // Initial action of mouse wheel down.
                    uint32_t wh_down_callback(uint32_t trigger_time, void* cb_arg) {
                        tap_code(KC_MS_WH_DOWN);
                        return REP_DELAY_MS; // Return constant delay for SCROLLDOWN.
                    }
                    token = defer_exec(REP_DELAY_MS, wh_down_callback, NULL); 
                }
            }
        } return false; // Skip normal handling.
	    
        case COPYACC:  // Copies the accession number to the clipboard
            if (record->event.pressed) {
                SEND_STRING(
                    SS_LSFT("`")
                    SS_LSFT("`")
                    SS_TAP(X_ENTER)
                    SS_DELAY(100)
                    SS_LSFT(SS_LCTL(SS_TAP(X_LEFT)))
                    SS_LCTL("c")
                    SS_LSFT(SS_TAP(X_HOME))
                    SS_TAP(X_DEL) 
                    SS_TAP(X_DEL) 
                );
            }
            return false;
        
        case OPENGE: // Pastes the accession number in GE PACs
            if (record->event.pressed) {
                SEND_STRING(
                    SS_LSFT(SS_TAP(X_TAB))
                    SS_TAP(X_END)
                    SS_DELAY(75)
                    SS_TAP(X_TAB)
                    SS_LCTL("v")
                    SS_DELAY(150)
                    SS_TAP(X_ENTER)
                );
            }
            return false;

        case OPENEPIC: // Pastes the accession number in EPIC
            if (record->event.pressed) {
                SEND_STRING(
                    SS_LCTL("2")
                    SS_DELAY(1500)
                    SS_LCTL("v")
                    SS_TAP(X_ENTER)
                    SS_DELAY(1500)
                    SS_LALT(SS_LSFT("a"))
                );
            }
            return false;
        
        case PASTE: // Pastes the accession number in EPIC
            if (record->event.pressed) {
                SEND_STRING(
                    SS_LCTL("v")
                );
            }
            return false;
			
		case WL_SOFTTISSUE:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_KP_1)
				);
			}
		return false;
		
		case WL_BONE:
			if (record->event.pressed) {
				SEND_STRING(				
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_KP_2)
				);
			}
		return false;
		
		case WL_BRAIN:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_KP_3)
				);
			}
		return false;
        
		case WL_STROKE:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_KP_0)
				);
			}
		return false;

		case WL_LUNG:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_KP_5)
				);
			}
		return false;

		case WL_HARDWARE:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_KP_6)
				);
			}
		return false;
		
		case WL_VASCULAR:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_KP_8)
				);
			}
		return false;
		
		case ARROW:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_A)
				);
			}
		return false;
		
		case MEASURE:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_M)
				);
			}
		return false;
		
		case ZOOM:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_LSFT("Z")
				);
			}
		return false;
		
		case ANNOTATIONS:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_Y)
				);
			}
		return false;
		
		case SPINE_C:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_C)
				);
			}
		return false;

		case SPINE_T:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_T)
				);
			}
		return false;

		case SPINE_L:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_BTN1)
					SS_DELAY(50)
					SS_TAP(X_L)
				);
			}
		return false;
		
		case DELETE:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_F15) 
				);
			}
		return false;
		
		case WHEELUP:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_MS_WH_UP)
				);
			}
		return false;
		
		case WHEELDOWN:
			if (record->event.pressed) {
				SEND_STRING(
					SS_TAP(X_MS_WH_DOWN)
				);
			}
		return false;
		
		case DICTATE: // Pastes the accession number in EPIC SEND_STRING(SS_TAP(X_F13));
			if (record->event.pressed) {
				SEND_STRING(SS_TAP(X_F13));	
			}
		return false;

		case PREVFIELD:
			if (record->event.pressed) {
				SEND_STRING(SS_TAP(X_F15));
			}
		return false;	
		
		case NEXTFIELD: //SEND_STRING(SS_TAP(X_F14));
			if (record->event.pressed) {
				SEND_STRING(SS_TAP(X_F14));
			}
		return false;
				  

    }

    return true; // Process all other keycodes normally.
}



/*  		case SCROLLDOWN:  // Toggles scroll wheel down. 
		  if (record->event.pressed) {  
			static bool held = false;  // Static variable to remember state.
			held = !held;  // Toggle between holding and releasing.
			if (held) {  // scroll down
			  register_code16(KC_MS_WH_DOWN);
			  wait_ms(100);
			} else {  // stop scrolling.
			  unregister_code16(KC_MS_WH_DOWN);
			}
		  }
		  return false;

		case SCROLLUP:  // Toggles scroll UP. 
		  if (record->event.pressed) {  
			static bool held = false;  // Static variable to remember state.
			held = !held;  // Toggle between holding and releasing.
			if (held) {  // scroll down
			  register_code16(KC_MS_WH_UP);
			} else {  // stop scrolling.
			  unregister_code16(KC_MS_WH_UP);
			}
		  }
		  return false;  */
		  
 /*    case SCROLLDOWN:
      if (record->event.pressed) {
        if (!held_down) {
          if (scroll_speed < 3) {
            scroll_speed++;
          }
          if (scroll_speed > 0) {
            for (int i = 0; i < scroll_speed; i++) {
              register_code16(KC_MS_WH_DOWN);
              unregister_code16(KC_MS_WH_DOWN);
              wait_ms(100 / scroll_speed);  // Add delay here.
            }
          } else {
            unregister_code16(KC_MS_WH_DOWN);
            unregister_code16(KC_MS_WH_UP);
          }
          held_down = true;
        } else {
          unregister_code16(KC_MS_WH_DOWN);
          unregister_code16(KC_MS_WH_UP);
          held_down = false;
        }
      }
      return false;

    case SCROLLUP:
      if (record->event.pressed) {
        if (!held_up) {
          if (scroll_speed > -3) {
            scroll_speed--;
          }
          if (scroll_speed < 0) {
            for (int i = 0; i < -scroll_speed; i++) {
              register_code16(KC_MS_WH_UP);
              unregister_code16(KC_MS_WH_UP);
              wait_ms(100 / -scroll_speed);  // Add delay here.
            }
          } else {
            unregister_code16(KC_MS_WH_DOWN);
            unregister_code16(KC_MS_WH_UP);
          }
          held_up = true;
        } else {
          unregister_code16(KC_MS_WH_DOWN);
          unregister_code16(KC_MS_WH_UP);
          held_up = false;
        }
      }
      return false; 
*/
