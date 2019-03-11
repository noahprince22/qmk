#include "Dactyl.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;
#define _QWERTY 0
#define _ALT 1
#define _ALTSH 2
#define _CTR 3
#define _SELECT 4
#define _SELECT_ALT 5
#define _SELECT_ALT_SHIFT 6
#define _FN3 7

//#define _FN4 6
#define _ADJUST 16
enum {
	TD_CPY_PST = 0,
	TD_CMD,
	TD_SLSH,
	TD_VRDSK
};
enum custom_keycodes {
	QWERTY,
	ALT,
	ALTSH,
	CTR,
	SELECT,
	SELECT_ALT,
	SELECT_ALT_SHIFT,
	FN3,
	ADJUST,
	dance_cln_finished,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS
#define KC_CAPW LGUI(X_LSHIFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(X_LSHIFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(X_LSHIFT(KC_4))       // Capture portion of screen
#define KC_CPYP LGUI(X_LSHIFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_X0 MT(MOD_LCTL, KC_ESC)
#define KC_TOGUP TG(4)
#define KC_REST RESET
#define KC_ALENT LT(_ALT, KC_ENT) // goes to alt layer when held, enter when tapped
#define KC_ALTSH MO(_ALTSH)
#define KC_CTR_L LM(_CTR, MOD_LCTL) // goes to ctrl layer when held, maybe behaves like regular control
#define KC_SEL_A OSL(_SELECT) // turns on the select oneshot, turns off when any key is pressed
#define KC_SELALTENT LT(_SELECT_ALT, KC_ENT) // goes to the alt select layer, which can move around but keeps select layer active
#define KC_SELALTSHIFT MO(_SELECT_ALT_SHIFT) // when shift + alt held down in select mode.
#define KC_FN3_A MO(_FN3)
#define KC_ADJUST_A MO(_ADJUST)

#define KC_X9 RGUI(KC_TAB)	//gui tab to switch desktops
#define KC_X10 TD(TD_VRDSK)

#define KC_COPY LGUI(KC_C)
#define KC_CUT LGUI(KC_X)
#define KC_PASTE LGUI(KC_V)

#define KC_SEL_L M(0)
#define KC_SEL_R M(1)
#define KC_SEL_U M(2)
#define KC_SEL_D M(3)

#define KC_SEL_L_WRD M(4)
#define KC_SEL_R_WRD M(5)
#define KC_SEL_PG_UP M(6)
#define KC_SEL_PG_D M(7)

#define KC_SEL_HOME M(8)
#define KC_SEL_END M(9)

#define KC_L_WRD M(10)
#define KC_R_WRD M(11)

#define KC_B_WRD M(12)

#define MOVE X_LALT // mac
// #define MOVE X_LCTRL // linux/windows



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-------------------------------------------.           ,----------------------------------_--------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+------|           |------+------+------+------+------|--------|
 * |A      |   Q  |   W  |   F  |   P  |   G  |           |   J  |   L  |   U  |   Y  |   :  |   \    |
 * |--------+------+------+------+------+----- |           |------+------+------+------+------|--------|
 * | ENT/ADJ|   A  |   R  |   S  |   T  |   D  |           |   H  |   N  |   E  |   I  |   O  | ENTER  |
 * |--------+------+------+------+------+------|           |------+------+------+------+------|--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |           |   K  |   M  |   ,  |   .  |  /   |RShift |
 * `--------+------+------+------+------+------'           `-------+------+------+------+------|--------|'
 * |CTR     |  ALT | GUI  | Left | Right|    1                1   | LEFT | RIGHT|  UP  | DOWN  | ~L1  |
 * `----------------------------------'                          `----------------------------------'
 *				6	5		4	   3		2				2		 3		4		5		6
 *                                 ,-------------.       ,-------------.
 *                                 |   6  |   5  |       | 5    |  6     |
 *                          ,------|------|------|       |------+--------+------.
 *                          |   1  |  2    |   4  |       | 4    |        |      |
 *                          |Backsp|GUI   |------|       |------|    1   |    2 |
 *                          |  acs |TAB   |   3  |       | 3    |        |      |
 *                         `--------------------'       `----------------------'
 
 
  	
 */
 
    //
	[_QWERTY] = KC_KEYMAP(
	//,----+----+----+----+----+----.										,----+----+----+----+----+----.
	  A  , 1  , 2  , 3  , 4  , 5  ,     									 6  , 7  , 8  , 9   , 0  , A,
	//,----+----+----+----+----+----.										,----+----+----+----+----+----.
		A , Q  , W  , E  , R  , T  ,    									  Y  , U  , I  , O , P  , B,
	//|----+----+----+----+----+----|   									|----+----+----+----+----+----|
      B, A  , S  , D  , F  , G  ,								      H  , J  , K  , L  ,C,D,
	//|----+----+----+----+----+----|										|----+----+----+----+----+----|
		C , Z  , X  , C  , V  , B  ,										    N  , M  ,E,F,G,H,
	//|----+----+----+----+----+----|										|----+----+----+----+----+----|
	  D,E,F,G,H,   ,										     ,I,J,K,L,   ,
	//`----+----+----+----+----+----'   									 `----+----+----+----+----+----'
	//							`----+----+----+'			`----+----+----'
										I,J,			 M, N,
	//							`----+----+----+'			`----+----+----'
											K,			O,
	//							`----+----+----+'			`----+----+----'
							    N,M ,L,			    B, B, B
	//							`----+----+----+'			`----+----+----'

	),

	[_ALT] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
		   ,    ,    ,    ,    ,    ,   							      ,    ,    ,     ,   ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,B_WRD,    ,    ,   							      ,L_WRD,UP ,R_WRD,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,    ,    ,    ,     							  END ,LEFT,DOWN,RIGHT,     ,   ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
  ALTSH ,  , CUT,COPY,PASTE,  ,							      ,    ,    ,    ,    ,   ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
   ADJUST_A,    ,    ,,   ,   ,    						       ,,   ,    ,    ,     ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
										  ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
											   ,			     ,
	//							`----+----+----+'			`----+----+----'
									,     ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
	),

	[_ALTSH] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
		   ,    ,    ,    ,    ,    ,   							      ,    ,    ,     ,   ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,    ,    ,    ,   							      ,    ,PGUP,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,    ,    ,    ,     							  HOME,    ,PGDN,    ,     ,   ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		  ,  ,  ,    ,    ,    ,							         ,    ,    ,    ,    ,   ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		    ,    ,    ,,   ,   ,    						          ,,   ,    ,    ,     ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
										  ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
											   ,			     ,
	//							`----+----+----+'			`----+----+----'
									,     ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
	),

	[_CTR] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
		   ,    ,    ,    ,    ,    ,   							      ,    ,    ,     ,   ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,    ,    ,    ,   							      ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,    ,    ,    ,     							      ,    ,    ,    ,    ,   ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		  ,  ,  ,    ,    ,    ,							         ,    ,    ,    ,    ,   ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		    ,    ,    ,,   ,   ,    						          ,,   ,    ,    ,     ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
										  ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
											   ,			     ,
	//							`----+----+----+'			`----+----+----'
									,     ,    ,			     ,    , SEL_A
	//							`----+----+----+'			`----+----+----'
	),

    [_SELECT] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
 SELALTSHIFT,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
									    ,    ,			         ,    ,
	//							`----+----+----+'			`----+----+----'
											    ,			     ,
	//							`----+----+----+'			`----+----+----'
							SELALTENT,     ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
	),

	[_SELECT_ALT] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							      ,SEL_L_WRD,SEL_U,SEL_R_WRD,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,     							  SEL_END,SEL_L,SEL_D,SEL_R,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
									    ,    ,			         ,    ,
	//							`----+----+----+'			`----+----+----'
											    ,			     ,
	//							`----+----+----+'			`----+----+----'
								    ,     ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
	),

    [_SELECT_ALT_SHIFT] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,     							  SEL_HOME,     ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							      ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
									    ,    ,			         ,    ,
	//							`----+----+----+'			`----+----+----'
											    ,			     ,
	//							`----+----+----+'			`----+----+----'
								    ,     ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
	),

	
	
	[_FN3] = KC_KEYMAP(
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		F12 , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
			, 3 , 3,  3, 3  , 3  ,         ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
			,    ,UP,    ,    ,    ,         ,    ,    ,    , UP ,    ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
			,LEFT,DOWN,RIGHT,    ,    ,          ,    ,    ,LEFT,DOWN,RIGHT,  
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X0 ,LALT,LGUI, X10,  ,BSPC,     SPC, UP ,QUOT,LEFT, DOWN ,RGHT,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
//		X3  , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9 , 0  ,MINS,
	//							`----+----+----+'			`----+----+----'
										PGUP,PGDN,			 END, HOME,
	//							`----+----+----+'			`----+----+----'
											PSCR,			DEL,
	//							`----+----+----+'			`----+----+----'
									BSPC, ,    ,			    , ENT, SPC
	//							`----+----+----+'			`----+----+----'

	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
	),
/*
	[_FN4] = KEYMAP( \
	_______, _______, M(3)   , M(2)     , _______,  M(4)  ,		 _______, _______, _______, _______, _______, _______, \
	_______, M(6)   , _______, _______  , _______, _______,		 _______, _______, _______, _______, _______, _______, \
	_______, _______, M(1)   ,TD(TD_CMD), _______, _______,		 _______, _______, _______, _______, KC_UP, _______, \
	M(7)   , M(8)   , M(9)   , _______  , _______, _______,		 _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, \
	_______, _______, _______, _______  , _______, _______,		 _______, _______, _______, _______, _______, _______, \
	_______, _______ , _______, _______  , _______, _______,	 _______, _______, _______, _______, _______, _______ \
	),*/

	/* Adjust (Lower + Raise)
* ,-----------------------------------------------------------------------------------.
* |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|Sat Up|Sat Dn|Val Up|Val Dn| RESET|      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |      |      |      |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |             |      |      |      |      |      |
* `-----------------------------------------------------------------------------------'
*/
	[_ADJUST] = KEYMAP( \
	KC_REST,QWERTY, _______, _______, _______, _______, _______, _______, _______, _______, _______  , _______, \
	KC_REST, QWERTY, _______, _______,   _______,  _______, _______, QWERTY,  _______, _______,  _______, _______, \
	KC_REST, _______   , _______   , _______, _______, _______, _______, _______, _______, _______, _______, _______, \
	KC_REST, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
	KC_REST, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_REST, \
	_______, _______, _______, _______, _______, _______, _______, _______, \
	_______, _______, _______, _______ \
	)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
	eeconfig_update_default_layer(default_layer);
	default_layer_set(default_layer);
}

/*
void dance_cln_finished(void){
register_code (KC_LGUI);
register_code(KC_TAB);
unregister_code(KC_TAB);
unregister_code(KC_LGUI); 
}*/

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (record->event.pressed) {
	switch (id) {
    	case 0: // select left
    	    SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_LEFT) SS_UP(X_LSHIFT));
//    	    set_oneshot_layer(_SELECT, ONESHOT_START)
    	    return false;

    	case 1: // select right
            SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_RIGHT) SS_UP(X_LSHIFT));
//    	    set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 2: // select up
            SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_UP) SS_UP(X_LSHIFT));
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 3: // select down
            SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_DOWN) SS_UP(X_LSHIFT));
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 4: // select left word
            SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_LSHIFT) SS_TAP(X_LEFT) SS_UP(X_LSHIFT) SS_UP(MOVE));
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 5: // select right word
            SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_LSHIFT) SS_TAP(X_RIGHT) SS_UP(X_LSHIFT) SS_UP(MOVE));
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 6: // select page up
            SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_PGUP) SS_UP(X_LSHIFT));
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 7: // select page down
            SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_PGDOWN) SS_UP(X_LSHIFT));
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 8: // select home
            SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_HOME) SS_UP(X_LSHIFT));
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 9: // select end
            SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_END) SS_UP(X_LSHIFT));
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

    	case 10: // left word
    	    SEND_STRING(SS_DOWN(MOVE) SS_TAP(X_LEFT) SS_UP(MOVE));
    		return false;

    	case 11: // right word
            SEND_STRING(SS_DOWN(MOVE) SS_TAP(X_RIGHT) SS_UP(MOVE));
            return false;

        case 12: // backspace left word
            SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_LSHIFT) SS_TAP(X_LEFT) SS_UP(X_LSHIFT) SS_UP(MOVE) SS_TAP(X_BSPACE));
            return false;
	}

	}
    return MACRO_NONE;
}

void cmd_commands(qk_tap_dance_state_t *state, void *user_data) {
}


void cmd(qk_tap_dance_state_t *state, void *user_data) {
}

qk_tap_dance_action_t tap_dance_actions[] = {
};
