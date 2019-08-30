#include "Dactyl.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;
#define _QWERTY 0
#define _ALT 1
#define _ALTSH 2
#define _FN 3
#define _SELECT 4
#define _SELECT_ALT 5
#define _SELECT_ALT_SHIFT 6
#define _FN3 7

//#define _FN4 6
enum {
	TD_CPY_PST = 0,
	TD_CMD,
	TD_SLSH,
 	TD_VRDSK
};
enum custom_keycodes {
	ALT,
	ALTSH,
	CTR,
	SELECT,
	SELECT_ALT,
	SELECT_ALT_SHIFT,
	FN3,
	ADJUST,
	dance_cln_finished,
	KC_SPACETHING = SAFE_RANGE,
	KC_GUITAB
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
#define KC_MALT M(20) // MO(_ALT) // goes to alt layer when held, maybe behaves like regular alt
#define KC_MSHIFT M(21) // MO(_ALTSH)
#define KC_FN_L M(22) // LM(_FN, MOD_LCTL) // goes to ctrl layer when held, maybe behaves like regular control
#define KC_SEL_A M(23) // OSL(_SELECT) // turns on the select oneshot, turns off when any key is pressed
#define KC_SELALT LT(_SELECT_ALT, KC_LALT) // goes to the alt select layer, which can move around but keeps select layer active
#define KC_SELALTSHIFT MO(_SELECT_ALT_SHIFT) // when shift + alt held down in select mode.
#define KC_FN3_A MO(_FN3)
//#define KC_GUITAB RWIN_T(KC_TAB)
#define KC_SHIFTSPC M(25)
#define KC_RESTL M(24)

#define KC_X9 RGUI(KC_TAB)	//gui tab to switch desktops
#define KC_X10 TD(TD_VRDSK)

#define KC_SAVE LCTL(KC_S)
#define KC_COPY LCTL(KC_C)
#define KC_S_COPY M(15)
#define KC_S_CUT M(16)
#define KC_CUT LCTL(KC_X)
#define KC_PASTE LCTL(KC_V)
#define KC_UNDO LCTL(KC_Z)
#define KC_ALTENT LALT(KC_ENT)
#define KC_REDO LCTL(LSFT(KC_Z))
#define KC_FORMAT LALT(LSFT(KC_L))
#define KC_DIR LALT(LSFT(KC_D))
#define KC_OPEN LALT(LSFT(KC_O))
#define KC_FINDA LALT(LSFT(KC_F))
#define KC_OOG LALT(LSFT(KC_4)) // Open in oposite group intellij
#define KC_RUN LALT(LCTL(KC_R)) // Run on cursor intellij
#define KC_DEBUG LALT(LCTL(KC_D)) // Debug on cursor intellij
#define KC_SRUN LSFT(LALT(LCTL(KC_R))) // Run on cursor intellij
#define KC_SDEBUG LSFT(LALT(LCTL(KC_D))) // Debug on cursor intellij
#define KC_MVRT LALT(KC_4) // Move window right (do a split) in intellij
#define KC_MVGRP LALT(LSFT(KC_4)) // Alternate the group of the window in intellij
#define KC_CLOSE LCTL(KC_W)
#define KC_REP LCTL(KC_R)
#define KC_REPA LALT(LSFT(KC_R))
#define KC_OPG LALT(KC_S) // Move to the opposite group intellij
#define KC_FIND LCTL(KC_F)
#define KC_P_TAB LCTL(KC_PGUP)
#define KC_N_TAB LCTL(KC_PGDN)
#define KC_PTAB LALT(KC_LBRC)
#define KC_NTAB LALT(KC_RBRC)

#define KC_SELALL LCTL(KC_A)

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

// #define MOVE X_LALT // mac
#define MOVE X_LCTRL // linux/windows

#define KC_AG_NORM AG_NORM


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
	  GRV  , 1  , 2  , 3  , 4  , 5  ,     									 6  , 7  , 8  , 9   , 0  , EQL,
	//,----+----+----+----+----+----.										,----+----+----+----+----+----.
		TAB , Q  , W  , E  , R  , T  ,    									  Y  , U  , I  , O , P  , MINS,
	//|----+----+----+----+----+----|   									|----+----+----+----+----+----|
      CLCK, A  , S  , D  , F  , G  ,								          H  , J  , K  , L  ,SCLN,QUOT,
	//|----+----+----+----+----+----|										|----+----+----+----+----+----|
		MSHIFT, Z  , X  , C  , V  , B  ,										    N  , M  ,COMM,DOT,SLSH,ENT,
	//|----+----+----+----+----+----|										|----+----+----+----+----+----|
	  FN3_A,LCTRL,LWIN,MSHIFT,LALT,   ,										     ,LBRC,RBRC,LCTRL,BSLS,   ,
	//`----+----+----+----+----+----'   									 `----+----+----+----+----+----'
	//							`----+----+----+'			`----+----+----'
										ESC,F6,			 FORMAT, DEL,
	//							`----+----+----+'			`----+----+----'
											HOME,			PGUP,
	//							`----+----+----+'			`----+----+----'
							    MALT, GUITAB,END,			    PGDN, BSPC, SPACETHING
	//							`----+----+----+'			`----+----+----'

	),
	[_ALT] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
		   ,    ,    ,    ,MVRT,    ,   							      ,    ,    ,     ,   ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,CLOSE,B_WRD,REP,    ,   							      ,L_WRD,UP ,R_WRD,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	   ,SELALL,SAVE,    ,FIND,    ,     							  END ,LEFT,DOWN,RIGHT,     ,   ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
  MSHIFT , UNDO , CUT,COPY,PASTE,  ,							      ,    ,    ,    ,    ,  ALTENT,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
      ,    ,    ,MSHIFT,   ,   ,    						                  ,PTAB,NTAB,    ,    ,     ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
										  ,    ,			 RUN,DEBUG,
	//							`----+----+----+'			`----+----+----'
											   ,			     ,
	//							`----+----+----+'			`----+----+----'
									,     ,    ,			     ,    ,SEL_A
	//							`----+----+----+'			`----+----+----'
	),

	[_ALTSH] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
		   ,    ,    ,    ,MVGRP ,    ,   							      ,    ,    ,     ,   ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,    ,REPA,    ,   							      ,    ,PGUP,OPEN,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,DIR,FINDA,    ,     							  HOME,    ,PGDN,    ,     ,   ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		  ,REDO ,  ,    ,   RUN,DEBUG,							         ,    ,    ,    ,    ,   ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,    ,    ,    ,    						          ,,   ,    ,    ,     ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
										  ,    ,			 SRUN,SDEBUG,
	//							`----+----+----+'			`----+----+----'
											   ,			     ,
	//							`----+----+----+'			`----+----+----'
							     MALT,     ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
	),

	[_FN] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
		   ,    ,    ,    ,    ,    ,   							      ,    ,    ,     ,   ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,    ,    ,    ,   							      ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
		   ,    ,    ,    ,    ,    ,     							      ,    ,    ,    , OPG,   ,
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
									,     ,    ,			     ,P_TAB,N_TAB
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
     MSHIFT,   , ,  ,  ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,MSHIFT,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
									    ,    ,			         ,    ,
	//							`----+----+----+'			`----+----+----'
											    ,			     ,
	//							`----+----+----+'			`----+----+----'
							      MALT,    ,    ,			     ,    ,
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
	 MSHIFT,UNDO ,S_CUT ,S_COPY ,PASTE ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,SELALTSHIFT,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|  								  |----+----+----+----+----+----|
	//							`----+----+----+'			`----+----+----'
									    ,    ,			         ,    ,
	//							`----+----+----+'			`----+----+----'
											    ,			     ,
	//							`----+----+----+'			`----+----+----'
								MALT,     ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
	),

    [_SELECT_ALT_SHIFT] = KC_KEYMAP(
	//,----+----+----+----+----+----.  								  ,----+----+----+----+----+----.
	       ,    ,    ,    ,    ,    ,   							       ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,   							       ,    ,  SEL_PG_UP  , ,    ,    ,
	//|----+----+----+----+----+----|   							 |----+----+----+----+----+----|
	       ,    ,    ,    ,    ,    ,     							  SEL_HOME,     ,  SEL_PG_D ,    ,    ,    ,
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
								 MALT,     ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
	),

	
	
	[_FN3] = KC_KEYMAP(
	//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
		F12 , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
	  ,    ,    ,    ,   ,     ,         ,    ,    ,    ,    ,    ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
			,    ,   ,    ,    ,    ,         ,    ,    ,    ,     ,    ,
	//|----+----+----+----+----+----|    |----+----+----+----+----+----|
		REST,AG_NORM,RESTL,    ,    ,    ,   ,    ,    ,   ,   ,      ,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
		   ,    ,   ,     ,  ,   ,            ,    ,    ,    ,    ,    ,
	//`----+----+----+----+----+----'    `----+----+----+----+----+----'
//		X3  , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9 , 0  ,MINS,
	//							`----+----+----+'			`----+----+----'
										  ,    ,			     ,    ,
	//							`----+----+----+'			`----+----+----'
											   ,			     ,
	//							`----+----+----+'			`----+----+----'
									 ,    ,    ,			     , SPC, SPC
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

typedef struct node {
   uint16_t keycode;
   struct node *next;
} node_t;

void enqueue(node_t **head, uint16_t keycode) {
   node_t *new_node = malloc(sizeof(node_t));
   if (!new_node) return;

   new_node->keycode = keycode;
   new_node->next = *head;

   *head = new_node;
}

uint16_t dequeue(node_t **head) {
   node_t *current, *prev = NULL;
   int retval = -1;

   if (*head == NULL) return -1;

   current = *head;
   while (current->next != NULL) {
      prev = current;
      current = current->next;
   }

   retval = current->keycode;
   free(current);

   if (prev)
      prev->next = NULL;
   else
      *head = NULL;

   return retval;
}

uint16_t remove(node_t **head, uint16_t keycode) {
   node_t *current, *prev = NULL;
   int retval = -1;

   if (*head == NULL) return -1;

   current = *head;
   while (current->keycode != keycode) {
      prev = current;
      current = current->next;
   }

   retval = current->keycode;
   free(current);

   if (prev)
      prev->next = current->next;
   else
      *head = NULL;

   return retval;
}

bool volatile shift_down=false;
bool volatile space_shift_down=false;
bool volatile gui_down=false;
bool volatile alt_down=false;
bool volatile select_active=false;
bool volatile pressed_something_else=false;
bool volatile pressed_something_else_gui=false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     static uint16_t space_held_timer;
     static node_t *last_key = NULL;

     // This bit of code makes it so that if I hold down the spacebar, it becomes a shift key, assuming
     // that I press another key after holding it down. If no other key is pressed, I clearly wasn't using it as
     // a shift key, and so it comes through as a space. The only consequence of this is that space is applied on
     // key up, and not key down. So I need to make sure the space has been released before typing another key
     // realistically, if I'm light on my fingers, this shouldn't be a problem.
     // I also make use of a timer, so I can hold on to space a little between keypresses for smoothness of use,
     // and have it not be a shift.
     // Later added a queue so that if you lift up space while some keys are still down, it acts as if this was a space
     // followed by all the key down events in order, and NOT a Shift. Brilliant.
     // We also wait until the last key goes up. It must go up before shift goes up.
     // It's a similar thing with the fn/gui/windows key. It should be a tab when I tap it, but if I use it as a
     // modifier, it's a modifier.
     if (keycode == KC_SPACETHING) {
           if (record->event.pressed) {
                space_held_timer = timer_read();
                space_shift_down = true;
                pressed_something_else=false;
                while(dequeue(&last_key) != -1) {};
                last_key = NULL;
           }
           else {
                space_shift_down = false;
                SEND_STRING(SS_UP(X_LSHIFT));
                if (!pressed_something_else) {
                   SEND_STRING(" ");
                }
                pressed_something_else=false;
           }
     }
     else if (keycode == KC_GUITAB) {
        if (record->event.pressed) {
          gui_down = true;
          pressed_something_else_gui=false;
          SEND_STRING(SS_DOWN(X_LGUI));
          layer_on(_FN);
        }
        else{
          gui_down = false;
          SEND_STRING(SS_UP(X_LGUI));
          layer_off(_FN);
          if(!pressed_something_else_gui) {
            SEND_STRING(SS_TAP(X_TAB));
          }
          pressed_something_else_gui=false;
        }
     }
     else {
        // press a key while shift is down
        if (timer_elapsed(space_held_timer) > 25 && record->event.pressed && space_shift_down) {
          enqueue(&last_key, keycode);
          return false; // we handled the keypress, swallow it and only hold down the shift once it's up
        }
        // release that key while shift is down
        if (timer_elapsed(space_held_timer) > 25 && !record->event.pressed && space_shift_down) {
            SEND_STRING(SS_DOWN(X_LSHIFT));
            register_code(keycode);
            remove(&last_key, keycode);
            pressed_something_else=true;
        }
        else if (record->event.pressed && gui_down) {
            pressed_something_else_gui =true;
        }
     }

     // They released space before releasing the last key, it doesn't count as a shift and we need to register that key
     if (last_key != NULL && !space_shift_down) {
       uint16_t unregistered_code = dequeue(&last_key);

       while(unregistered_code != -1) {
         register_code(unregistered_code);
         unregistered_code = dequeue(&last_key);
       }
     }

  return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    bool p = record->event.pressed;
	switch (id) {
    	case 0: // select left
    	    if (p) {
    	      SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_LEFT) SS_UP(X_LSHIFT));
    	    }
    	    else {
    	      SEND_STRING(SS_UP(X_LEFT) SS_UP(X_LSHIFT));
    	    }
//    	    set_oneshot_layer(_SELECT, ONESHOT_START)
    	    return false;

    	case 1: // select right
    	    if (p) {
              SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_RIGHT));
    	    }
    	    else {
    	      SEND_STRING(SS_UP(X_RIGHT) SS_UP(X_LSHIFT));
    	    }
//    	    set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 2: // select up
            if(p) {
              SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_UP));
            }
            else {
              SEND_STRING(SS_UP(X_UP) SS_UP(X_LSHIFT));
            }
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 3: // select down
            if (p) {
              SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_DOWN));
            }
            else {
              SEND_STRING(SS_UP(X_DOWN) SS_UP(X_LSHIFT));
            }
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 4: // select left word
            if (p) {
              SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_LSHIFT) SS_DOWN(X_LEFT));
            }
            else {
              SEND_STRING(SS_UP(X_LEFT) SS_UP(X_LSHIFT) SS_UP(MOVE));
            }
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 5: // select right word
            if(p) {
              SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_LSHIFT) SS_DOWN(X_RIGHT));
            }
            else {
              SEND_STRING(SS_UP(X_RIGHT) SS_UP(X_LSHIFT) SS_UP(MOVE));
            }
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 6: // select page up
            if (p) {
              SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_PGUP));
            }
            else {
              SEND_STRING(SS_UP(X_PGUP) SS_UP(X_LSHIFT));
            }
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 7: // select page down
            if (p) {
              SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_PGDOWN));
            }
            else {
              SEND_STRING(SS_UP(X_PGDOWN) SS_UP(X_LSHIFT));
            }
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 8: // select home
            if(p) {
              SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_HOME));
            }
            else {
              SEND_STRING(SS_UP(X_HOME) SS_UP(X_LSHIFT));
            }
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

        case 9: // select end
            if(p) {
              SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_END));
            }
            else {
              SEND_STRING(SS_UP(X_END) SS_UP(X_LSHIFT));
            }
//            set_oneshot_layer(_SELECT, ONESHOT_START)
            return false;

    	case 10: // left word
    	    if (p) {
    	      SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_LEFT));
    	    }
    	    else {
      	      SEND_STRING(SS_UP(X_LEFT) SS_UP(MOVE));
    	    }
    		return MACRO_NONE;

    	case 11: // right word
    	    if(p) {
              SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_RIGHT));
    	    }
    	    else {
              SEND_STRING(SS_UP(X_RIGHT) SS_UP(MOVE));
    	    }
            return MACRO_NONE;

        case 12: // backspace left word
            if (p) {
              SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_BSPACE));
            }
            else {
              SEND_STRING(SS_UP(X_BSPACE) SS_UP(MOVE));
            }
            return MACRO_NONE;

        case 13:
            if(p) {
              SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_LCTRL) SS_DOWN(X_Z));
            }
            else {
              SEND_STRING(SS_UP(X_Z) SS_UP(X_LSHIFT) SS_UP(X_LCTRL));
            }
            return false;

        case 14: //format
            if (p) {
              SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LCTRL) SS_DOWN(X_L));
            }
            else {
              SEND_STRING(SS_UP(X_L) SS_UP(X_LCTRL) SS_UP(X_LALT));
            }
            return false;

        case 15: //scopy
            if (p) {
              SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_C));
            }
            else {
              SEND_STRING(SS_UP(X_C) SS_UP(MOVE) SS_TAP(X_ESCAPE));
              select_active=false;
              layer_off(_SELECT_ALT);
              layer_on(_ALT);
            }
            return MACRO_NONE;

        case 16: //scut
            if (p) {
              SEND_STRING(SS_DOWN(MOVE) SS_DOWN(X_X));
            }
            else {
              SEND_STRING(SS_UP(X_X) SS_UP(MOVE) SS_TAP(X_ESCAPE));
              select_active=false;
              layer_off(_SELECT_ALT);
              layer_on(_ALT);
            }
            return MACRO_NONE;

         case 17: // go to dir
            if (p) {
              SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LSHIFT) SS_DOWN(X_D));
            }
            else {
              SEND_STRING(SS_UP(X_D) SS_UP(X_LALT) SS_UP(X_LSHIFT));
            }
            return MACRO_NONE;

         case 18: // open
            if (p) {
              SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LSHIFT) SS_DOWN(X_O));
            }
            else {
              SEND_STRING(SS_UP(X_O) SS_UP(X_LALT) SS_UP(X_LSHIFT));
            }
            return MACRO_NONE;

         case 19: // find in all
            if(p) {
              SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_DOWN(X_F));
            }
            else {
              SEND_STRING(SS_UP(X_F) SS_UP(X_LCTRL) SS_UP(X_LSHIFT));
            }
            return MACRO_NONE;

         case 20: // malt
            if(p) {
              alt_down=true;
              if (select_active) {
                if (shift_down) {
                  SEND_STRING(SS_UP(X_LSHIFT));
                  layer_on(_SELECT_ALT_SHIFT);
                }
                else {
                  layer_on(_SELECT_ALT);
                }
              }
              else {
                if (shift_down) {
                  SEND_STRING(SS_UP(X_LSHIFT));
                  layer_on(_ALTSH);
                }
                else {
                  layer_on(_ALT);
                }
              }
            }
            else {
              alt_down=false;
              select_active = false;
              layer_off(_ALT);
              layer_off(_ALTSH);
              layer_off(_SELECT_ALT_SHIFT);
              layer_off(_SELECT_ALT);
            }
            return false;

         case 21: // mshift
            if(p) {
              shift_down=true;
              if(alt_down) {
                if(select_active) {
                  layer_on(_SELECT_ALT_SHIFT);
                }
                else {
                  layer_on(_ALTSH);
                }
              }
              else {
                SEND_STRING(SS_DOWN(X_LSHIFT));
              }
            }
            else {
              shift_down=false;
              layer_off(_SELECT_ALT_SHIFT);
              layer_off(_ALTSH);
              if (alt_down) {
                if(select_active) {
                  layer_on(_SELECT_ALT);
                }
                else {
                  layer_on(_ALT);
                }
              }
              SEND_STRING(SS_UP(X_LSHIFT));
            }
            return false;
         case 22: // the function key acts like a function key but also activates a layer
            if(p) {
              layer_on(_FN);
              SEND_STRING(SS_DOWN(X_LGUI));
            }
            else {
              layer_off(_FN);
              SEND_STRING(SS_UP(X_LGUI));
            }
            return false;

         case 23:
           if(p) {
             select_active = !select_active;
             layer_on(_SELECT_ALT);
           }
           return false;

         case 24: // restl - reset all layers. In case something gets stuck.
           layer_off(1);
           layer_off(2);
           layer_off(3);
           layer_off(4);
           layer_off(5);
           layer_off(6);
           layer_off(7);
           layer_on(_QWERTY);
           SEND_STRING(SS_UP(X_LCTRL) SS_UP(X_LSHIFT) SS_UP(MOVE) SS_UP(X_LALT) SS_UP(X_LGUI));

         case 25:  // space key. when it's down, shift is down. but it still does a space
           if (p) {
                space_shift_down = true;
                pressed_something_else=false;
                SEND_STRING(SS_DOWN(X_LSHIFT));
           }
           else {
                space_shift_down = false;
                SEND_STRING(SS_UP(X_LSHIFT));
                if (pressed_something_else) {
                   SEND_STRING(" ");
                }
                pressed_something_else=false;
           }

           return false;

	}

    return MACRO_NONE;
}


void cmd_commands(qk_tap_dance_state_t *state, void *user_data) {
}


void cmd(qk_tap_dance_state_t *state, void *user_data) {
}

qk_tap_dance_action_t tap_dance_actions[] = {
};
