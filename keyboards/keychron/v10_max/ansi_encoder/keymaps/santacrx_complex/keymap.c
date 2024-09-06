/* Copyright 2024 @ santacrx
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
 * 
 * This program is based on the base offered by Keychron and any other 
 * sources as identified in the comments and README. I'm just a hobbyist, 
 * not responisuble if you use any of this and brick your keeb. 
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "print.h"
#include "math.h"

// clang-format off

//========================
// Standard Keeb QMK defs
//========================

enum layers{
    _FN,
    _BASE,
    _LV,
    _DAT,
    _VS,
    _CAD,
    _NA,
    _NUM
};

// adding custom keycodes for layer cycling using the knob
enum custom_keycodes{
  LAYERUP = NEW_SAFE_RANGE, //read in reddit abobut the _NEW being added. testing to see if it'll compile this way
  LAYERDN,
  LAYERGO,
  LAYER00,
  WIN_ZUM,
  LV_WHIL,
  LV_FOR,
  LV_LVAR,
  LV_GVAR,
  EX_ADDR,
  EX_ADDC,
  XS_DEGR,
  XS_NTIL,
  XS_MICR,
  XS_SECT
};

//#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_FN] = LAYOUT_ansi_89(
        _______,  QK_RBT,       KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_CALC,            _______,
        _______,  _______,      BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
        _______,  RGB_TOG,      RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           KC_PGUP,
        _______,  _______,      RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,   _______,  _______,  _______,  _______,  _______,  _______,            _______,           KC_PGDN,
        _______,  LSFT_T(KC_NO),_______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,      _______,            _______,  _______,  LAYERGO,                       _______,            _______,                      _______,  _______,  _______),

    [_BASE] = LAYOUT_ansi_89(
        _______,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   TG(_NUM),              KC_PSCR,
        XS_NTIL,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,               KC_DEL,
        XS_DEGR,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,               KC_HOME,
        XS_SECT,  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            RSFT_T(KC_ENT),        KC_END,
        XS_MICR,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RCTL(KC_APP), KC_UP,
        XXXXXXX,  KC_LCTL,  KC_LWIN,            KC_LALT,  KC_SPC,   LAYER00,                       KC_SPC,             RALT(KC_APP),                 KC_LEFT,      KC_DOWN, KC_RGHT),

    [_LV] = LAYOUT_ansi_89(
        WIN_ZUM,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        LV_WHIL,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        LV_FOR,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        LV_LVAR,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        LV_GVAR,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        XXXXXXX,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [_DAT] = LAYOUT_ansi_89(
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        EX_ADDR,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        EX_ADDC,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        XXXXXXX,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        XXXXXXX,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [_VS] = LAYOUT_ansi_89(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        XXXXXXX,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        XXXXXXX,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [_CAD] = LAYOUT_ansi_89(
        KC_MUTE,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        XXXXXXX,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        XXXXXXX,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [_NA] = LAYOUT_ansi_89(
        KC_MPLY,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        XXXXXXX,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        XXXXXXX,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [_NUM] = LAYOUT_ansi_89(
        KC_MS_BTN3, XXXXXXX,  XXXXXXX,  	XXXXXXX,  	XXXXXXX,      XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,            _______,
        XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,   XXXXXXX, KC_PSLS,   KC_PAST, KC_PMNS,  XXXXXXX,  _______,  _______,  _______,            _______,
        XXXXXXX,    _______,  XXXXXXX,    KC_MS_UP,  	XXXXXXX,      XXXXXXX,    XXXXXXX,   KC_P7,   KC_P8,     KC_P9,   KC_PPLS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,            KC_PGUP,
        XXXXXXX,    XXXXXXX,  KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,  XXXXXXX,    XXXXXXX,   KC_P4,   KC_P5,     KC_P6,   KC_PPLS,  XXXXXXX,  XXXXXXX,            _______,            KC_PGDN,
        XXXXXXX,    KC_MS_BTN2,    		    XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,   XXXXXXX, KC_P0,     KC_P1,   KC_P2,    KC_P3,    KC_PENT,  XXXXXXX,  XXXXXXX,  _______,
        KC_NUM,     _______,  _______,       		     	_______,      KC_MS_BTN1, _______,                       KC_P0,             KC_PDOT,                      _______,  _______,  _______),
};

// map what the rotary encoder for the knob does
#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_FN] =   { ENCODER_CCW_CW(LAYERDN, LAYERUP) },
    [_BASE] = { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT) },
    [_LV] =   { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT) },
    [_DAT] =  { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT) },
    [_VS] =   { ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_CAD] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NA] =   { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_NUM] =  { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP) }
};
#endif // ENCODER_MAP_ENABLE

//=========
//  MODS 
//=========

/*
// DIPSWITCH
// ---------
// map what the dipswitch does: turn lights on or off (LH=ON, RH=OFF)
#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        if (active){
          rgb_matrix_disable_noeeprom();
        } else {
          rgb_matrix_enable_noeeprom();
        }
    }
    return true;
}
#endif
*/

// KNOB LAYER SELECTION WITH LIGHTS PER LAYER
// ------------------------------------------
// Modded to match/use Matrix effects [See Readme Sources, 2.1]

// create constant placeholders for RGB light mode and HSV
uint8_t rgbLastMode; 
HSV rgbLastHsv;
uint8_t rgbLastVal;
bool rgbLastState;
static int8_t prevLayerInt;
// global constants  for the layer change gig
static uint8_t currLayerID;
static uint8_t currLayerMask;  // mask is ID  ORed with b0010
// global constant for Zoom On off for Macro
static uint8_t winZoomOn = 0;
// init color selction per layer ID
static uint8_t MkeyColors[7][3] = {
  {HSV_TEAL},   //0
  {HSV_TEAL},   //1
  {HSV_GOLD},   //2  _LV
  {HSV_GREEN},  //3  _DAT
  {HSV_PURPLE}, //4  _VS
  {HSV_RED},    //5  _CAD
  {HSV_PINK}    //6  _NA
};
// M column indeces definition for color changes
static uint8_t M_leds_idx[] = {15,31,47,62,77};


// initialization functions
void eeconfig_init_user(void) {  // EEPROM is getting reset!
  uprintf("eeconfig init ran\n");
  // set default layer to _BASE
  default_layer_set(2); // 2 = b0010
  layer_state_set(2);
  // use the non noeeprom versions, to write these values to EEPROM too
  rgb_matrix_enable(); // Enable RGB by default
  rgb_matrix_sethsv(HSV_TEAL);  // Set it to teal by default
  rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN); // set the default
  // update constant value
  rgbLastMode = rgb_matrix_get_mode();
  rgbLastHsv = rgb_matrix_get_hsv();
  rgbLastVal = rgb_matrix_get_val();
  rgbLastState = rgb_matrix_is_enabled();
  prevLayerInt = 0;
  currLayerID = 1;
  winZoomOn = 0;
}

//after keeb initialized, make sure  to have _Base on and with proper lights
void keyboard_post_init_user(void) {
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  layer_state_set(2);
  rgb_matrix_enable();
  rgb_matrix_sethsv(HSV_TEAL);  // Set it to teal by default
  rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN); // set the default
}

// calculate mask value, and also set color for M column. this is a test
void updateKnobLayer(void){
  currLayerMask = (int) pow(2,currLayerID) | 2; // 2^current layer, then or'd to 2 = 0000 0010
  uprintf("updateKnob called. ID:%2u, Mask:%2u\n",currLayerID, currLayerMask);
  //layer_clear();
  layer_state_set(currLayerMask);
  /*
  // change color of M column based on ID layer selected
  for(uint8_t col = 0; col < 5; ++col){
    rgb_matrix_set_color(M_leds_idx[col],MkeyColors[currLayerID][0],MkeyColors[currLayerID][1],MkeyColors[currLayerID][2]);
  }
  */
}

/*
// Helper for implementing tap vs. long-press keys. Given a tap-hold
// key event, replaces the hold function with `long_press_keycode`.
static bool process_tap_or_long_press_key(keyrecord_t* record, uint16_t long_press_keycode) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
      tap_code16(long_press_keycode);
    }
    return false;  // Skip default handling.
  }
  return true;  // Continue default handling.
}
*/

// Add the behaviour for custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Get current mod and one-shot mod states.
  const uint8_t mods = get_mods();
  const uint8_t oneshot_mods = get_oneshot_mods();

  switch (keycode) {

    // Cylce M layer by 1, or if SHIFT change RGB mode
    //------------------------------------------------
    case LAYERUP:
      // Our logic will happen on presses, nothing is done on releases
      if (record->event.pressed) {
        if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
          print("SHIFT + LAYERUP!\n");
          tap_code16(KC_VOLU);
        } else { // no shift held
          // +1. then check if we are within the range, if not, go back to 1
          currLayerID+=1;
          if (currLayerID > 6) {
              currLayerID = 1;
          }
          uprintf("LAYERUP! New Setting: %2u\n",currLayerID);
          rgb_matrix_sethsv_noeeprom(MkeyColors[currLayerID][0],MkeyColors[currLayerID][1],MkeyColors[currLayerID][2]);
          }
      }
      return false;

    // Cycle M layer down 1  
    //----------------------
    case LAYERDN:
      // Our logic will happen on presses, nothing is done on releases
      if (record->event.pressed) { 
        if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
          print("SHIFT + LAYERDN!\n");
          tap_code16(KC_VOLD);
        } else { // no shift held
          // -1. then check if we are within the range, if not, go back to 1
          currLayerID-=1;
          if (currLayerID < 1) {
              currLayerID = 6;
          }
          uprintf("LAYERDN! New Setting:%2u\n",currLayerID);
          rgb_matrix_sethsv_noeeprom(MkeyColors[currLayerID][0],MkeyColors[currLayerID][1],MkeyColors[currLayerID][2]);
        }
      }
      return false;

    // Process the M layer change/ application
    //-----------------------------------------
    case LAYERGO:
      // Our logic will happen on presses, nothing is done on releases
      if (record->event.pressed) { 
        print("LAYERGO! \n");
        updateKnobLayer();
      }
      return false;

    case LAYER00:
      // Our logic will happen on presses, nothing is done on releases
      if (record->event.pressed) { 
        print("LAYER 0!\n");
        //layer_clear();
        layer_state_set(1);
      }
      return false;
    
    
    // MACROS!!!
    //-------------
    
    // use windows magnifier on one press, and kill it when clicked again
    case WIN_ZUM:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) { 
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }
      uprintf("WIN_ZUM. Was %1u, ",winZoomOn);
      if (winZoomOn==0){
        tap_code16(LGUI(KC_EQL));
        winZoomOn=1;
      }else{
        tap_code16(LGUI(KC_ESC));
        winZoomOn=0;
      }
      uprintf("is %1u\n",winZoomOn);
      return false;
    
    // tell labview to bring the while loop tool
    case LV_WHIL:
      print("LV_GVAR\n");
      // Our logic will happen on presses, nothing is done on releases
      if (record->event.pressed) { 
        tap_code16(LCTL(KC_SPC)); 
        SEND_STRING(SS_DELAY(150) "while loop" SS_DELAY(150));
        tap_code(KC_ENT);
      }
      return false;
    
    // tell labview to bring the for loop tool
    case LV_FOR:
      print("LV_FOR\n");
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) { 
        tap_code16(LCTL(KC_SPC)); 
        SEND_STRING(SS_DELAY(150) "for loop" SS_DELAY(150));
        tap_code(KC_ENT);
      }
      return false;
    
    // tell labview to bring the local variable tool
    case LV_LVAR:
      print("LV_LVAR\n");
      // Our logic will happen on presses, nothing is done on releases
      if (record->event.pressed) { 
        tap_code16(LCTL(KC_SPC)); 
        SEND_STRING(SS_DELAY(150) "local" SS_DELAY(150));
        tap_code(KC_ENT);
      }
      return false;
    
    // tell labview to bring the global  variable tool
    case LV_GVAR:
      print("LV_GVAR\n");
      // Our logic will happen on presses, nothing is done on releases
      if (record->event.pressed) { 
        tap_code16(LCTL(KC_SPC)); 
        SEND_STRING(SS_DELAY(150) "global" SS_DELAY(150));
        tap_code(KC_ENT);
      }
      return false;
    
    // tell excel to add a row, delete if shift is held
    case EX_ADDR:
      // Our logic will happen on presses, nothing is done on releases
      if (record->event.pressed) { 
        // send commands depending if shift is held or not
        if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
          // Temporarily delete shift.
          del_oneshot_mods(MOD_MASK_SHIFT);
          unregister_mods(MOD_MASK_SHIFT); 
          // send macro 
          tap_code16(LALT(KC_H));
          send_string("dr");
          // Restore mods.
          register_mods(mods);            
        } else { // no mods held
          tap_code16(LALT(KC_H));
          send_string("ir");
        }
      }
      return false;
    
    // tell excel to add a column, delete if shift is held
    case EX_ADDC:
      // Our logic will happen on presses, nothing is done on releases
      if (record->event.pressed) { 
        // send commands depending if shif is held or nor 
        if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
          // Temporarily delete shift.
          del_oneshot_mods(MOD_MASK_SHIFT);
          unregister_mods(MOD_MASK_SHIFT); 
          // send macro 
          tap_code16(LALT(KC_H));
          send_string("dc");
          // Restore mods.
          register_mods(mods);            
        } else { // no mods held
          tap_code16(LALT(KC_H));
          send_string("ic");
        }
      }
      return false;

    case XS_NTIL:
      if (record->event.pressed) {
        if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
          // Temporarily delete shift.
          del_oneshot_mods(MOD_MASK_SHIFT);
          unregister_mods(MOD_MASK_SHIFT);  
          // do the shifted behavior
          register_code(KC_LALT);
          tap_code(KC_P1);
          tap_code(KC_P6);
          tap_code(KC_P5);
          unregister_code(KC_LALT);
          // Restore mods.
          register_mods(mods);            
        } else { // no shift held
          register_code(KC_LALT);
          tap_code(KC_P1);
          tap_code(KC_P6);
          tap_code(KC_P4);
          unregister_code(KC_LALT);
        }
      }
      return false;

    case XS_DEGR:
      if(record->event.pressed){
        register_code(KC_LALT);
        tap_code(KC_P0);
        tap_code(KC_P1);
        tap_code(KC_P7);
        tap_code(KC_P6);
        unregister_code(KC_LALT);
      }
      return false;
      
    case XS_MICR:
      if(record->event.pressed){
        register_code(KC_LALT);
        tap_code(KC_P2);
        tap_code(KC_P3);
        tap_code(KC_P0);
        unregister_code(KC_LALT);
      }
      return false;
      
    case XS_SECT:
      if(record->event.pressed){
        register_code(KC_LALT);
        tap_code(KC_P2);
        tap_code(KC_P1);
        unregister_code(KC_LALT);
      }
      return false;


    // Process other keycodes normally
    //---------------------------------
    default:
      
      return true;
  }
  return false;
}


// function to detect layer change and perform color change per layer
layer_state_t layer_state_set_user(layer_state_t state) {
  // determine layer jump and direction
  uint8_t current_layer = get_highest_layer(state);
  uprintf("state: %2u; biton32(state): %2u; highest layer: %2u; prevLayer: %2u; knobLayer: %2u;\n",state,biton32(state),current_layer,prevLayerInt,currLayerID);
  // Perform action based on which highes layer is active
  switch(current_layer){
  case 0:
    // _FN: sprial with color based on M layer ID
    rgb_matrix_enable();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_BAND_SPIRAL_VAL);
    rgb_matrix_sethsv_noeeprom(MkeyColors[currLayerID][0],MkeyColors[currLayerID][1],MkeyColors[currLayerID][2]);
    break;
  case 7:
    // _NUM
    // rolling rainbox, aka party!
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
    break;
  default:
    // _BASE and above, 
    // If user changed color mode while in _NUM, update the constant value
    if ((rgb_matrix_get_mode() != RGB_MATRIX_BAND_SPIRAL_VAL) && (prevLayerInt == 0) && (currLayerID == 1)) {
      printf("We are back from 0, no change in layers, and RBG mode changed, updating last value.\n");
      // get new desired value when changed by user
      rgbLastState = rgb_matrix_is_enabled();
      rgbLastMode = rgb_matrix_get_mode();
      rgbLastHsv = rgb_matrix_get_hsv();
      rgbLastVal = rgb_matrix_get_val();
      // write the current states to eeprom
      rgbLastState ? rgb_matrix_enable() : rgb_matrix_disable();
      rgb_matrix_mode(rgbLastMode);
      rgb_matrix_sethsv(rgbLastHsv.h,rgbLastHsv.s,rgbLastVal);
    } else {
      // if no change, go to last settings without writing to eeprom
      rgbLastState ? rgb_matrix_enable_noeeprom() : rgb_matrix_disable_noeeprom();
      rgb_matrix_mode_noeeprom(rgbLastMode);
      rgb_matrix_sethsv_noeeprom(rgbLastHsv.h,rgbLastHsv.s,rgbLastVal);
    }

    
    // _BASE and the macro layers
    /*
    // perform  layer masking update/activation
    if (currLayerID != prevLayerInt){
      print("updateKnob called\n");
      // change color of M column based on ID layer selected
    }
    
    for(uint8_t col = 0; col < 5; ++col){
      rgb_matrix_set_color(M_leds_idx[col],MkeyColors[currLayerID][0],MkeyColors[currLayerID][1],MkeyColors[currLayerID][2]);
    }
    */
    break;
  }
  prevLayerInt = current_layer;
  return state;
}

// Custom light functions based on layers and indicator used to only show active keys
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state); // get current layer

    // This will turn off keys that are transparent or KC_NO for _FN and _NUM
    if ((layer  == 7)) {  
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) { // for every matrix row
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) { // for every column
                uint8_t index = g_led_config.matrix_co[row][col]; // get the index number

                if (index >= led_min && index < led_max && index != NO_LED) { //if within led lims and not flagged as no led
                    if(keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_TRNS ||
                    keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_NO) { // if transparent or KC_NO, turn light off
                        rgb_matrix_set_color(index, RGB_BLACK);
                    }
                }
            }
        }
    }
    
    // If we are on _BASE layer and CAPS is on, OR on _NUM layer, then only highlight letters. 
    if ((host_keyboard_led_state().caps_lock && layer > 0)){// ||  layer == 7) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] != LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_BLACK);
            }
        }
    // else, we can color M column if within the layer range
    }else if((layer > 1 && layer < 7)){
      //print("M column color being called\n");
      //uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));
      HSV h = {MkeyColors[layer][0],MkeyColors[layer][1],MkeyColors[layer][2]};
      RGB hr = hsv_to_rgb(h);
      for(uint8_t col = 0; col < 5; ++col){
        rgb_matrix_set_color(M_leds_idx[col],hr.r,hr.g,hr.b);
      }
    }
    

    return false;
}

