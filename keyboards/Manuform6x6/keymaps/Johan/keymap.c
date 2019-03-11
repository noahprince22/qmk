#include "Manuform.h"
#include "action_layer.h"
#include "eeconfig.h"
#include QMK_KEYBOARD_H

#include "keymap_nordic.h"






extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _FN3 5
//#define _FN4 6
#define _ADJUST 16
enum {
	TD_CPY_PST = 0,
	TD_CMD,
	TD_SLSH,
	TD_VRDSK
};
enum custom_keycodes {
	COLEMAK = SAFE_RANGE,
	QWERTY,
	DVORAK,
	LOWER,
	RAISE,
	FN3,
//	FN4,
	ADJUST,
	dance_cln_finished,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS
#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))       // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_X0 MT(MOD_LCTL, KC_ESC)
#define KC_LDWN TG(_LOWER)				//Numpad
#define KC_LUP TG(_RAISE)
#define KC_TOGUP TG(4)
#define KC_REST RESET
#define KC_X3 LT(_FN3,KC_TAB)		//function layer 4 ie macros when held tab when pressed
#define KC_X4 LT(_ADJUST, KC_ENT) //Shift when held enter when pressed
#define KC_X5 LT(RAISE, KC_P0)  //Raise to functions when held P0 when pressed
#define KC_X6 TD(TD_SLSH)				//slash vs backslash
#define KC_X7 TD(TD_CPY_PST)		//single tap is copy double is paste
#define KC_X8 TD(TD_CMD)			//single tap is cmd double is ipconfig


#define KC_Xs9 RGUI(KC_TAB)	//gui tab to switch desktops
#define KC_X10 TD(TD_VRDSK)
#define KC_SEMC LSFT(KC_COMM)
#define KC_EQ RSFT(KC_0)
#define KC_BSL RALT(KC_MINS)

#define KC_SLS LSFT(KC_7)
#define KC_RBC RALT(KC_0)
#define KC_LBC RALT(KC_7)
#define KC_QUO LSFT(KC_2)
#define KC_LB RALT(KC_8)
#define KC_RB RALT(KC_9)



#define KC_NO_ACUT NO_ACUT
#define KC_NO_RBRC NO_RBRC
#define KC_NO_GRV NO_GRV
#define KC_NO_ACUT NO_ACUT
#define KC_NO_QUOT NO_QUOT
#define KC_NO_PLUS NO_PLUS

#

/*
#define KC_NOR_A KC_NO_AA
#define KC_NOR_OS KC_NO_OSLH
#define KC_NOR_AE KC_NO_AE
#define KC_NO_LCBR KC_NO_LBCR
#define KC_NO_LBRC  KC_NO_LBRC 
#define KC_NO_RBRC NO_RBRC
#define KC_NO_RCBR	 KC_NO_RCBR	
#define KC_NO_SCLN  KC_NO_SCLN 
#define KC_NO_COLN KC_NO_COLN 
#define KC_NO_GRV KC_NO_GRV
#define KC_NO_HALF KC_NO_HALF
*/

#define KC_XLgn M(1)
#define KC_EMAL M(2)
#define KC_WWWX M(3)
#define KC_NTAB M(4)
#define KC_0CA M(6)
#define KC_PASS M(10)
#define KC_IPCF M(11)
#define KC_CMD M(16)
#define KC_OP M(12)
#define KC_OC M(13)
#define KC_OD M(14)
#define KC_TCLK M(15)
#define KC_ESCT MT(MOD_LCTL, KC_ESC)
#define KC_GUIT M(0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-------------------------------------------.           ,----------------------------------_--------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+------|           |------+------+------+------+------|--------|
 * |Tab\FN3 |   Q  |   W  |   F  |   P  |   G  |           |   J  |   L  |   U  |   Y  |   :  |   \    |
 * |--------+------+------+------+------+----- |           |------+------+------+------+------|--------|
 * | ENT/ADJ|   A  |   R  |   S  |   T  |   D  |           |   H  |   N  |   E  |   I  |   O  | ENTER  |
 * |--------+------+------+------+------+------|           |------+------+------+------+------|--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |           |   K  |   M  |   ,  |   .  |  /   |RShift |
 * `--------+------+------+------+------+------'           `-------+------+------+------+------|--------|'
 * |CTR     |  ALT | GUI  | Left | Right|      |           |      |      | LEFT | RIGHT|  UP  | DOWN |
 * `--------------------------------------------'           --------------------------------------------'
 *      		    | Left | Right		|Backsp| L2 | 	 |Enter| Space|		 DEL | SCRN |
 *				   -----------------------------		    -----------------------------
 *                				 |      |ctrTab|			|     |      |
 *				   ------------------------------		    -----------------------------
 *								 |PGUP  |PGDWN |			|Home |END|
 
 222222222
 | 4|  2| 3  | 1 |				|  1 | 3  | 2  | 4  |

 |   1 |  2  |					|  2  | 1   |
 |  3  |  4  |					|  4  | 3   |

 
 
 
 2a
		6	5		4	 
		3		2			2		 3		4		5		6
 *                                 ,-------------.       ,-------------.
 *                                 |   6  |   5  |       | 5    |  6     |
 *                          ,------|------|------|       |------+--------+------.
 *                          |      |      |   4  |       | 4    |        |      |
 *                          |Backsp|GUI   |------|       |------|    1   |    2 |
 *                          |  acs |TAB   |   3  |       | 3    |        |      |
 *32233222`--------------------'       `----------------------'
 
 questions about backslash, right brace quote, 
 */
			[_QWERTY] = KC_KEYMAP(
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		CAPS,RALT,QUO,HOME,LBC,RBC,    SLCK,END,BSL,INS ,DEL,LGUI,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		ESC, 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9 , 0  ,SEMC,
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O , P  ,LBRC,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		LSFT , A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN ,QUOT ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		LCTL , Z  , X  , C  , V  , B  ,      N  , M  ,EQ,EQL,DOT,COMM,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		   ,	,LALT,SLS ,SPC,BSPC,	   RSFT,ENT,MINUS,SLSH,,     ,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X3  , 1  , LEFT, LDWN  , UP  , PGDN ,   PGUP, DOWN ,LUP  , RIGHT , 5  ,MINS
	),
	
			[_COLEMAK] = KC_KEYMAP(
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		EQL, 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9 , 0   ,MINS,
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		X3 , Q  , W  , F  , P  , G  ,      J  , L  , U  , Y  ,SCLN,BSLS,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		X4 , A  , R  , S  , T  , D  ,      H  , N  , E  , I  , O  ,ENT,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		LSFT, Z  , X  , C  , V  , B  ,     K  , M  ,COMM,DOT ,SLSH,GRV,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		ESCT,LALT,LGUI,   1,  1 ,GRV,     DEL ,   ,LEFT,RIGHT,   ,QUOT,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		   ,    ,LEFT,RIGHT,BSPC,LDWN,    ENT ,SPC ,UP ,DOWN,    ,    ,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
	       ,     ,HOME,END, GUIT, PSCR,    DEL , LUP, PGUP , PGDN ,     , 
	),
	


	[_DVORAK] = KC_KEYMAP(
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		EQL, 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9 , 0  ,MINS,
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		TAB ,QUOT,COMM,DOT , P  , Y  ,      F  , G  , C  , R  , L  ,MINS,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		X0 , A  , O  , E  , U  , I  ,      D  , H  , T  , N  , S  ,SLSH,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		LSFT,SCLN, Q  , J  , K  , X  ,      B  , M  , W  , V  , Z  , X4 ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		X3 ,LCTL,LALT,LGUI, LDWN ,SPC ,     BSPC, UP ,LEFT,DOWN, UP ,RGHT,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X3  , 1  , 2  , 3  , 4  , 5  ,      2  , 2  , 2  , 2 , 2  ,MINS,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X3  , 1  , 2  , 3  , 4  , 5  ,      2  , 2  , 2  , 2 , 2  ,MINS
	),
/*
	[_LOWER] = KC_KEYMAP(
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		ESC , 1  , 2 , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  , EQL ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		DEL ,CAPP,LEFT,RGHT, UP ,LBRC,     RBRC, P4 , P5 , P6 ,PLUS,PIPE,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
			,CPYP, UP ,    ,DOWN,LCBR,     RCBR, P1 , P2 , P3 ,MINS,    ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
			,LEFT,DOWN,RIGHT,    ,    ,     DEL ,   , P0 ,PDOT,    ,  NLCK, 
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X0 ,LALT,LGUI, X10, LDWN ,BSPC,     SPC, UP ,QUOT,LEFT, DOWN ,RGHT,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X3  , 1  ,REST, 3  ,    , 5  ,      6  ,    , 8  , 9 , 0  ,MINS
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
	),

	[_RAISE] = KC_KEYMAP(
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		ESC ,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,    ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		DEL ,MPRV,MNXT,VOLU,PGUP,UNDS,     EQL ,HOME,    ,    ,    ,BSLS,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|88
		LSFT,MSTP,MPLY,VOLD,PGDN,MINS,     PLUS,END,COMM ,    ,UP ,    ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		,    ,    , X3 ,    ,    ,         ,    ,    ,LEFT,DOWN,RIGHT,    
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X0 ,LALT,LGUI, X10, LDWN ,BSPC,     SPC, UP ,QUOT,LEFT, DOWN ,RGHT,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X3  , 1  , 2  , 3  ,   , 5  ,      6  ,   , 8  ,REST, 0  ,MINS
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
	),*/
	
	[_LOWER] = KC_KEYMAP(
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		GRV, OP ,OC  , OD ,  LB, RB   ,         ,    ,    ,LBRC,RBRC,  ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		  ,     ,WWWX,EMAL,    ,TCLK,         ,    ,    ,CMD ,PASS,   ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		   ,0CA ,     ,   ,    ,    ,         ,    , UP ,IPCF,     ,   ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		  ,    ,XLgn,     ,    ,    ,         ,LEFT,DOWN,RIGHT,    ,   ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		REST,    ,    ,    ,    , REST  ,         ,    ,    ,    ,    ,REST,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		REST,  ,    ,    ,    ,LDWN,	   LUP ,LUP ,    ,     ,   , ,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X3  ,   ,   ,    ,    ,    ,          ,    ,    ,    ,    ,MINS
	),

	
	[_RAISE] = KC_KEYMAP(
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		   ,    ,   ,    ,  LB,RB ,         ,    ,    ,    ,   ,    ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		F1 , F2 , F3 , F4 , F5 ,F6 , 		F7 , F8 , F9 ,F10 ,F11 ,F12,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		   ,    ,   ,    ,    , LPRN,         , MPRV,MPLY,MNXT,MUTE,VOLU,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		   ,    ,   ,    ,    ,    ,         ,    ,    ,    ,   ,VOLD,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		 REST,    ,   ,    ,    ,    ,         ,    ,    ,    ,   ,REST,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		REST,   ,    ,    ,    ,LDWN,	   LUP,LUP , LUP,    ,    ,    ,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X3  ,   ,   ,    ,    ,    ,          ,    ,    ,    ,    ,MINS
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
		X0 ,LALT,LGUI, X10, LDWN ,BSPC,     SPC, UP ,QUOT,LEFT, DOWN ,RGHT,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X3  , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9 , 0  ,MINS,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		X3  , 1  , 2  , 3  , 4  , 5  ,      2  , 2  , 2  , 2 , 2  ,MINS
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
	_______, COLEMAK, QWERTY, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, RESET  , KC_REST, \
	_______, QWERTY, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  DEBUG, _______, \
	_______, KC_1   , KC_1   , _______, _______, _______, _______, _______, _______, _______, _______, _______, \
	_______, _______, _______, COLEMAK, _______, _______, _______, _______, _______, _______, _______, _______, \
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
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
	
	switch (id) {
	case 0:
		if (record->event.pressed) {
			return MACRO(D(LGUI), T(TAB), U(LGUI), END);
		}
	case 1:
		if (record->event.pressed) {
			SEND_STRING("admin"SS_TAP(X_TAB)"1111"SS_TAP(X_ENTER));
		return false;	break;
		//	return MACRO(I(10), T(A), T(D), T(M), T(I), T(N), T(TAB), T(1), T(1),T(1), T(1), T(ENTER), END );
		}
	case 2:
		if (record->event.pressed) {
			SEND_STRING("YourEmail");
			return false;	break;
		}
	case 3:
		if (record->event.pressed) {
			SEND_STRING("Frequentwebsite"SS_TAP(X_ENTER));
						return false;	break;
		}
	case 4:
		if(record->event.pressed) {
			return MACRO(I(10), D(LCTRL), T(T), T(V), T(ENTER), U(LCTRL), END);
		}
		
	case 5:{
			return  MACRO_TAP_HOLD_LAYER(record, MACRO(TYPE(KC_X), END), _LOWER);	
		}
	case 6: {
			if(record->event.pressed) 
			return MACRO(I(10), T(0), T(C), T(TAB), T(TAB), T(A), T(TAB), END);
		}
	case 10: {
		if(record->event.pressed) {
		SEND_STRING("");
			return false; break;}
	}		
	case 11: {
		if(record->event.pressed) {
			SEND_STRING("ipconfig /all");
					return false; break;}
	}
	case 12: {
	if(record->event.pressed) 
		return MACRO( I(10),T(TAB), T(O), T(P), T(TAB),T(ENTER), T(TAB),T(TAB),T(TAB),T(Z),T(R),T(TAB),T(ENTER), END );
	}	
		case 13: {
	if(record->event.pressed) 
		return MACRO( I(10),T(TAB), T(O), T(T), T(TAB),T(ENTER), T(TAB),T(TAB),T(TAB),T(Z),T(R),T(TAB),T(ENTER), END );
	}	
		case 14: {
	if(record->event.pressed) 
		return MACRO( I(10),T(TAB), T(I), T(N), T(TAB),T(ENTER), T(TAB),T(TAB),T(TAB),T(I),T(N),T(TAB),T(ENTER), END );
	}	
		case 15: {
	if(record->event.pressed) 
		SEND_STRING(""SS_TAP(X_TAB)""SS_TAP(X_TAB)SS_TAP(X_ENTER));
		return false; break;
	}
		case 16: {
	if(record->event.pressed) {
	MACRO(T(LGUI), W(50));}
	else{
	SEND_STRING("cmd"SS_TAP(X_ENTER));}
		return false; break;
	}
		break;
	}		
	return MACRO_NONE;
}
//return MACRO_NONE;


void cmd_commands(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		action_macro_play(MACRO(D(LCTRL), T(C), U(LCTRL),END));
	}
	else if (state->count ==2){
		action_macro_play(MACRO(D(LCTRL), T(V), U(LCTRL),END));
	}
	else {
		action_macro_play(MACRO(D(LCTRL), T(A), T(C), U(LCTRL),END));
	}
}


void cmd(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count==1){
		action_macro_play(MACRO(D(LGUI), T(R),W(255), U(LGUI),W(255), T(C), T(M), T(D), T(ENTER),END));
	}
	else if (state->count == 2) {
		action_macro_play(MACRO(D(LGUI), T(R), U(LGUI), T(C), T(M), T(D), T(ENTER),W(255),W(255), T(I), T(P), T(C), T(O), T(N), T(F), T(I), T(G), T(SPACE), T(SLASH), T(A), T(L), T(L),T(ENTER),END));
	}
	else{
		action_macro_play(MACRO(D(LGUI), T(R),W(255), U(LGUI),W(255), T(C), T(M), T(D), T(ENTER), W(255), T(P), T(I), T(N), T(G),T(SPACE), D(LCTRL), T(V), U(LCTRL), END));
	}
}
void SLSH_BSLSH(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code (KC_SLSH);
		unregister_code (KC_SLSH);
	}
	else{
		register_code (KC_BSLS);
		unregister_code (KC_BSLS);
	}
}
void VirtualDesktop(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) 
		action_macro_play(MACRO(D(LGUI),D(LCTRL),T(LEFT),U(LCTRL),U(LGUI),END));
	else if(state->count==2)
		action_macro_play(MACRO(D(LGUI),D(LCTRL),T(RIGHT),U(LCTRL),U(LGUI),END));
}
	
qk_tap_dance_action_t tap_dance_actions[] = {
	
	//Tap once for Esc, twice for Caps Lock
	[TD_CPY_PST] = ACTION_TAP_DANCE_FN(cmd_commands),
	[TD_SLSH]= ACTION_TAP_DANCE_FN(SLSH_BSLSH),
	[TD_CMD]=ACTION_TAP_DANCE_FN(cmd),
	[TD_VRDSK]=ACTION_TAP_DANCE_FN(VirtualDesktop)
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
	
	
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case QWERTY:
		if (record->event.pressed) {
			#ifdef AUDIO_ENABLE
			PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
			#endif
			persistent_default_layer_set(1UL<<_QWERTY);
		}
		return false;
		break;
	case COLEMAK:
		if (record->event.pressed) {
			#ifdef AUDIO_ENABLE
			PLAY_NOTE_ARRAY(tone_colemak, false, 0);
			#endif
			persistent_default_layer_set(1UL<<_COLEMAK);
		}
		return false;
		break;
	case DVORAK:
		if (record->event.pressed) {
			#ifdef AUDIO_ENABLE
			PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
			#endif
			persistent_default_layer_set(1UL<<_DVORAK);
		}
		return false;
		break;
	case LOWER:
		if (record->event.pressed) {
			layer_on(_LOWER);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		} else {
			layer_off(_LOWER);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		}
		return false;
		break;
	case RAISE:
		if (record->event.pressed) {
			layer_on(_RAISE);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		} else {
			layer_off(_RAISE);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		}
		return false;
		break;
	case ADJUST:
		if (record->event.pressed) {
			layer_on(_ADJUST);
		} else {
			layer_off(_ADJUST);
		}
		return false;
		break;
	}
	return true;
}
