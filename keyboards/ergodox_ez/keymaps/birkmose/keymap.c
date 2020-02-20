#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include <print.h>
#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
//#define NO_TH ALGR(KC_T)
//#define NO_ETH ALGR(KC_D)
#define PT KC_TRANSPARENT
#define KC_DK_SINGLE_QUOTE KC_BSLASH
enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  EPRM,
  DE_LSPO,
  DE_RSPC,
  NO_LSPO,
  NO_RSPC,
  TILDE,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
  SINGLE_HOLD_INT = 8
};


uint16_t get_first_td(void);
int cur_dance (qk_tap_dance_state_t *state);
int cur_danceTyped (int type, qk_tap_dance_state_t *state);
//Tap Dance Declarations
enum {
  TD_ESC_CAPS = 0,
  TD_LAY1_OR_3,
  TD_CMD_C,
  TD_CMD_V,
  TD_CMD_Z,
  TD_CMD_X,
  TD_a_A,
  TD_LVL0_TKR2,
  SOME_OTHER_DANCE,
  TD_DBL_OR_SINGLE_QUOTE,
  TD_SIGNLE_QUOTE_OR_ASTERIX,
  TD_PG_UP_HOME,
  TD_PG_DOWN_END,
  TD_MAX // ALWAYS LEAVE THIS IN THE END!!
};

static uint16_t active_tapdances[TD_MAX] = {0};
void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
   // register_code (KC_C);
  } else
  if (state->count == 2) {
    register_code (KC_B);
  } else {
    register_code (KC_A);
  }
}



void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
   // unregister_code (KC_C);
 layer_on(1);
  } else
  if (state->count == 2) {
    unregister_code (KC_B);
  } else {
    unregister_code (KC_A);
  }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// https://github.com/naps62/ergodox-layout/blob/master/keymap.c
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   | 1  ! | 2  @ | 3  # | 4  $ | 5  % | Lang |           | Esc  | 6  ^ | 7  & | 8  * | 9  ( | 0  ) | Bckspc |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  L2  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |    å   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   S  |  D   |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|  L1  |           |  L1  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  L1  | `  ~ | ' "  | \  | |  L2  |                                       |  {   |  }   | [  { | ]  } |  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.       ,---------------.
 *                                        | Home  | End  |       | PgUp  |Insert |
 *                                 ,------|-------|------|       |-------+-------+------.
 *                                 |      |       | LGui |       | Del   |       |      |
 *                                 | Alt  | LGui  |------|       |-------| Enter |Space |
 *                                 |      |       | LGui |       | Bcsp  |       |      |
 *                                 `---------------------'       `----------------------'
 */
  [0] = LAYOUT_ergodox(
      // left hand
      KC_EQUAL,         KC_1,           KC_2,       KC_3,           KC_4,           KC_5,           KC_LEFT,
      KC_DELETE,        KC_Q,           KC_W,       KC_E,           KC_R,           KC_T,            TD(TD_LAY1_OR_3),
      KC_BSPACE,        LT(4,KC_A),     KC_S,       KC_D,           KC_F,     LT(5,KC_G),
      LCTL(KC_LSHIFT),        KC_Z,   KC_X,       KC_C,           KC_V,   KC_B,              MT(MOD_HYPR,KC_TAB),
      LT(5,KC_GRAVE),   KC_QUOTE,       LALT(KC_LSHIFT),            KC_LEFT,        KC_TAB,

                                                                                                LALT_T(KC_APPLICATION),     KC_LGUI,
                                                                                                                            KC_HOME,
                                                                            LT(2,KC_DOT),           LT(2,KC_ENTER),                   KC_END,
      // right hand
      KC_RIGHT,         KC_6,               KC_7,               KC_8,       KC_9,           KC_0,                   KC_MINUS,
      LSFT(KC_7),      KC_Y,               KC_U,               KC_I,       KC_O,           KC_P,                   NO_AM,
                        KC_H,               LT(2,KC_J),               KC_K,       KC_L,           LT(2,KC_SCOLON),        LGUI_T(KC_QUOTE),
      MT(MOD_HYPR, KC_LGUI),      KC_N,               KC_M,               KC_COMMA,   KC_DOT,         KC_SLASH,               MT(MOD_HYPR,KC_END),
                                            LALT_T(KC_ESCAPE),  KC_DOWN,    KC_LBRACKET,    KC_RBRACKET,            KC_A,
      KC_LALT,          KC_RALT,
      KC_PGUP,
      KC_PGDOWN,        RSFT_T(KC_SPACE),   TD(TD_LVL0_TKR2)),
/* Keymap 1: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   | 1  ! | 2  @ | 3  # | 4  $ | 5  % | Lang |           | Esc  | 6  ^ | 7  & | 8  * | 9  ( | 0  ) | Bckspc |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  L2  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |    å   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   S  |  D   |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|  L1  |           |  L1  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  L1  | `  ~ | ' "  | \  | |  L2  |                                       |  {   |  }   | [  { | ]  } |  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.       ,---------------.
 *                                        | Home  | End  |       | PgUp  |Insert |
 *                                 ,------|-------|------|       |-------+-------+------.
 *                                 |      |       | LGui |       | Del   |       |      |
 *                                 | Alt  | LGui  |------|       |-------| Enter |Space |
 *                                 |      |       | LGui |       | Bcsp  |       |      |
 *                                 `---------------------'       `----------------------'
 */
  [1] = LAYOUT_ergodox(
      // LEFT hand
        PT,         KC_F1,                  KC_F2,              KC_F3,                  KC_F4,              KC_F5,          PT,
        PT,         NO_LCBR,                KC_AT,              KC_LCBR,                KC_RCBR,            KC_PIPE,        PT,
        PT,         KC_HASH,                KC_DLR,             KC_LPRN,                PT,                 PT,
        PT,         KC_PERC,                KC_CIRC,            KC_LBRACKET,            PT,                 KC_TILD,        PT,
        PT,         PT,                     PT,                 PT,                     PT,
                                                                                                            PT,                 PT,
                                                                                                                                PT,
                                                                                    PT,                     PT,                 PT,
    // RIGHT hand
        PT,         KC_F6,                  KC_F7,              KC_F8,                  KC_F9,              KC_F10,         KC_F11,
        TG(3),         KC_UP,                  KC_7,               KC_8,                   KC_9,               KC_ASTR,        KC_F12,
                    PT,                     KC_4,               KC_5,                   KC_6,               KC_PLUS,        PT,
        PT,         KC_AMPR,                KC_1,               KC_2,                   KC_3,               KC_BSLASH,      PT,
                                            PT,                 KC_DOT,                 KC_0,               KC_EQUAL,       RESET,
        PT,         PT,
        PT,
        PT,         KC_A,                   KC_B),
/* Keymap 2: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   | 1  ! | 2  @ | 3  # | 4  $ | 5  % | Lang |           | Esc  | 6  ^ | 7  & | 8  * | 9  ( | 0  ) | Bckspc |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  L2  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |    å   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   S  |  D   |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|  L1  |           |  L1  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  L1  | `  ~ | ' "  | \  | |  L2  |                                       |  {   |  }   | [  { | ]  } |  L1  |
 *   `------------------f---------------'                                       `----------------------------------'
 *                                        ,--------------.       ,---------------.
 *                                        | Home  | End  |       | PgUp  |Insert |
 *                                 ,------|-------|------|       |-------+-------+------.
 *                                 |      |       | LGui |       | Del   |       |      |
 *                                 | Alt  | LGui  |------|       |-------| Enter |Space |
 *                                 |      |       | LGui |       | Bcsp  |       |      |
 *                                 `---------------------'       `----------------------'
 */

  [2] = LAYOUT_ergodox(
    // LEFT hand
    PT,             KC_F1,              KC_F2,                  KC_F3,              KC_F4,              KC_F5,              KC_F11,
    PT,             PT,                 PT,                     NO_LESS,           NO_GRTR,                 PT,                 PT,
    PT,             RALT(KC_2),         KC_MS_LEFT,             KC_MS_DOWN,         PT,                 LSFT(KC_0),
    PT,             KC_MINUS,                 PT,                 PT,                     PT,                 PT,                 PT,
    PT,             KC_SLASH,                 PT,                 KC_MS_BTN1,             KC_MS_BTN2,
                                                                                                        PT,             PT,
                                                                                                                            PT,
                                                                                        PT,             PT,                 PT,
    // RIGHT HAND
    KC_F12,         KC_F6,              KC_F7,                  KC_F8,              KC_F9,              KC_F10,             KC_SLASH,
    RALT(NO_LESS),  NO_LESS,            NO_LPRN,                NO_RPRN,            NO_GRTR,            PT,                 PT,
                    TD(TD_DBL_OR_SINGLE_QUOTE),         NO_LCBR,                NO_RCBR,            LSFT(KC_0),         PT,                 KC_DK_SINGLE_QUOTE,
    RALT(KC_EQUAL),  TILDE,                 NO_LBRC,                NO_RBRC,            KC_MEDIA_NEXT_TRACK,PT,                 PT,
                                        KC_AUDIO_VOL_UP,        KC_AUDIO_VOL_DOWN,  KC_AUDIO_MUTE,      KC_F,               RESET,
    PT,             PT,
    PT,
    PT,             PT,                 LSFT(KC_DOT)),
/* Keymap 5: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   | 1  ! | 2  @ | 3  # | 4  $ | 5  % | Lang |           | Esc  | 6  ^ | 7  & | 8  * | 9  ( | 0  ) | Bckspc |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  L2  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |    å   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   S  |  D   |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|  L1  |           |  L1  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  L1  | `  ~ | ' "  | \  | |  L2  |                                       |  {   |  }   | [  { | ]  } |  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.       ,---------------.
 *                                        | Home  | End  |       | PgUp  |Insert |
 *                                 ,------|-------|------|       |-------+-------+------.
 *                                 |      |       | LGui |       | Del   |       |      |
 *                                 | Alt  | LGui  |------|       |-------| Enter |Space |
 *                                 |      |       | LGui |       | Bcsp  |       |      |
 *                                 `---------------------'       `----------------------'
 */

  [3] = LAYOUT_ergodox(
// LEFT hand
    PT,                 PT,                 PT,                 PT,                     PT,                 PT,                     PT,
    PT,                 PT,                 PT,                 PT,                     PT,                 PT,                     PT,
    PT,                 PT,                 PT,                 PT,                     LT(5,KC_F),         PT,
    PT,                 PT,                 PT,                 PT,                     PT,                 PT,                     PT,
    PT,                 PT,                 PT,                 PT,                     PT,
                                                                                                            PT,                     PT,
                                                                                                                                    PT,
                                                                                        PT,                 PT,                     PT,


    PT,                 PT,                 PT,                 PT,                     PT,                 PT,                     PT,
    PT,                 PT,                 PT,                 PT,                     PT,                 PT,                     PT,
                        PT,                 LT(5, KC_J),                 PT,                     PT,                 PT,                     PT,
    PT,                 PT,                 PT,                 PT,                     PT,                 PT,                     PT,
                                            PT,                 PT,                     PT,                 PT,                     PT,
    PT,                 PT,
    PT,
    PT,                 PT,                 PT),

/* Keymap 3: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   | 1  ! | 2  @ | 3  # | 4  $ | 5  % | Lang |           | Esc  | 6  ^ | 7  & | 8  * | 9  ( | 0  ) | Bckspc |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  L2  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |    å   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   S  |  D   |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|  L1  |           |  L1  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  L1  | `  ~ | ' "  | \  | |  L2  |                                       |  {   |  }   | [  { | ]  } |  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.       ,---------------.
 *                                        | Home  | End  |       | PgUp  |Insert |
 *                                 ,------|-------|------|       |-------+-------+------.
 *                                 |      |       | LGui |       | Del   |       |      |
 *                                 | Alt  | LGui  |------|       |-------| Enter |Space |
 *                                 |      |       | LGui |       | Bcsp  |       |      |
 *                                 `---------------------'       `----------------------'
 */

  [4] = LAYOUT_ergodox(
      //  LEFT hand
    PT,                 PT,                PT,                  PT,                 PT,             PT,             PT,
    PT,                 PT,                PT,                  PT,                 PT,             PT,             PT,
    PT,                 PT,                PT,                  PT,                 PT,             PT,
    PT,                 TD(TD_CMD_Z),      TD(TD_CMD_X),        TD(TD_CMD_C),       TD(TD_CMD_V),   PT,             PT,
    PT,                 PT,                PT,                  PT,                 PT,
                                                                                                    PT,             PT,
                                                                                                                    PT,
                                                                                    PT,             PT,             PT,

    // RIGHT hand
    PT,                 PT,                 PT,                 PT,                 PT,             PT,             LALT(LCTL(KC_DELETE)),
    PT,                 PT,                 PT,                 KC_UP,              PT,             PT,             PT,
                        PT,                 KC_LEFT,            KC_DOWN,            KC_RIGHT,       PT,             PT,
    PT,                 PT,                 PT,                 PT,                 PT,             PT,             PT,
                                            PT,                 PT,                 PT,             PT,             PT,
    PT,                 PT,
    PT,
    PT,                 PT,                 PT),


/* Keymap 4: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   | 1  ! | 2  @ | 3  # | 4  $ | 5  % | Lang |           | Esc  | 6  ^ | 7  & | 8  * | 9  ( | 0  ) | Bckspc |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  L2  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |    å   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   S  |  D   |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|  L1  |           |  L1  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  L1  | `  ~ | ' "  | \  | |  L2  |                                       |  {   |  }   | [  { | ]  } |  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.       ,---------------.
 *                                        | Home  | End  |       | PgUp  |Insert |
 *                                 ,------|-------|------|       |-------+-------+------.
 *                                 |      |       | LGui |       | Del   |       |      |
 *                                 | Alt  | LGui  |------|       |-------| Enter |Space |
 *                                 |      |       | LGui |       | Bcsp  |       |      |
 *                                 `---------------------'       `----------------------'
 */

  [5] = LAYOUT_ergodox(
// LEFT hand
    PT,                 PT,                 PT,                 PT,                 PT,             PT,                 PT,
    PT,                 PT,                 PT,                 LALT(LSFT(KC_7)),   KC_KP_SLASH,    PT,                 PT,
    PT,                 RALT(KC_BSLASH),    PT,                 KC_GRAVE,           KC_TILD,             PT,
    PT,                 PT,                 PT,                 PT,                 PT,             PT,                 PT,
    PT,                 PT,                 PT,                 PT,                 PT,
                                                                                                    PT,                 PT,
                                                                                                                        PT,
                                                                                    PT,             PT,                 PT,

    // RIGHT hand
    PT,                 PT,                 PT,                 PT,                 PT,             PT,                 PT,
    LALT(LSFT(KC_7)),   KC_GRAVE,           PT,                 PT,                 KC_TILD,        PT,                 PT,
                        PT,                 LALT(LSFT(KC_8)),   LALT(LSFT(KC_9)),   PT,             PT,                 PT,
    LALT(LSFT(KC_7)),   PT,                 PT,                 PT,                 PT,             PT,                 PT,
                                            PT,                 PT,                 PT,             PT,                 PT,
    PT,                 PT,
    PT,
    PT,                 PT,                 PT),
};
uint16_t get_first_td(void)
{
    uint16_t maxTime = 0;
    int maxTimer = TD_MAX;
    for (int i = 0; i < TD_MAX; i++)
    {
        if (active_tapdances[i] != 0)
        {
            uint16_t elapsedTime = timer_elapsed(active_tapdances[i]);
            if (elapsedTime > maxTime)
            {
                maxTime = elapsedTime;
                maxTimer = i;
            }
        }
    }
    if (maxTimer > 0)
    {
        uprintf("Max timer: %d, %d\n", maxTimer, maxTime);
    }
    return maxTimer;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t max_td = get_first_td();
    switch (max_td) {
        case TD_LVL0_TKR2:
        break;
    }
    #ifdef CONSOLE_ENABLE
    uprintf("TI: %d, KL: kc: %u, col: %u, row: %u, pressed: %u\n", timer_read(), keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
  switch (keycode) {
    case DE_LSPO:
      perform_space_cadet(record, KC_LSFT, KC_LSFT, KC_8);
      return false;
    case DE_RSPC:
      perform_space_cadet(record, KC_LSFT, KC_LSFT, KC_9);
      return false;
    case NO_LSPO:
      perform_space_cadet(record, KC_LSFT, KC_LSFT, KC_8);
      return false;
    case NO_RSPC:
      perform_space_cadet(record, KC_LSFT, KC_LSFT, KC_9);
      return false;
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
    case TILDE:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("]")" ");
      }

      return false;
  }
  return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
}

uint32_t layer_state_set_user(uint32_t state) {
  uint32_t layer = biton32(state);
  uprintf("%d, %d layer activated\n", state, layer);
  if (state & 0b1000) {
  if (state & 0b100000) {
      println("Layer 5 is active activating layer 2");
      state = state | 0b100;
  }
  else if (state & 0b100) {
      println("Layer 2 is active turning it of");
      state = state & ~0b100;
  }
  }


  if (state & 0b10000000) layer = 7;
  else if (state & 0b1000000) layer = 6;
  else if (state & 0b100000) layer = 5;
  else if (state & 0b10000) layer = 4;
  else if (state & 0b100) layer = 2;
  else if (state & 0b10) layer = 1;

  uprintf("LAYER: %d\n", layer);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
    //  ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
     ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
return cur_danceTyped(-1, state);
}
int cur_danceTyped (int type, qk_tap_dance_state_t *state) {
    if (type != -1) {
        uint16_t time = timer_read();
        if (time == 0) time = 1;
        active_tapdances[type] = time;
    }
    uprintf("count: %d\n", state->count);
    if (state->interrupted)
    print("Interupted\n");
    if (state->pressed)
    print("Pressed\n");;  if (state->count == 1) {
    if (state->interrupted && state->pressed)  {print("INT\n"); return SINGLE_HOLD_INT;}
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
 }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
/*  switch (xtap_state.state) {
    case SINGLE_TAP: layer_invert≠dd(1); break;
    case SINGLE_HOLD_INT:
    case SINGLE_HOLD: layer_on(3); break;
    case DOUBLE_TAP:  break;
    //case DOUBLE_HOLD: register_code(KC_LALT); break;
    //case DOUBLE_SINGLE_TAP: register_code(KC_); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
  */
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  uprintf("RScount: %d\n", state->count);
    if (state->interrupted)
    print("RSInterupted\n");
    if (state->pressed)
    print("RSPressed\n");

  switch (xtap_state.state) {
    case SINGLE_TAP: layer_invert(4); break;
    case DOUBLE_TAP: layer_invert(1); break;
  }
  xtap_state.state = 0;
}
void td_lvl0_tkr2_always (qk_tap_dance_state_t *state, void *user_data) {

print("always\n");
}
void td_lvl0_tkr2_finished (qk_tap_dance_state_t *state, void *user_data) {

print("fh\n");
  xtap_state.state = cur_danceTyped(TD_LVL0_TKR2,state);
  switch (xtap_state.state) {
    case SINGLE_HOLD_INT: register_code(KC_LCTRL); break;//print("Unhandled singled hold int fh\n"); break;
    case SINGLE_TAP: register_code(KC_LSHIFT);register_code(KC_COMMA); break;
    case DOUBLE_TAP: register_code(KC_LSHIFT);register_code(KC_COMMA);unregister_code(KC_COMMA); register_code(KC_COMMA); break;
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    //case DOUBLE_SINGLE_TAP: register_code(KC_); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void td_lvl0_tkr2_reset (qk_tap_dance_state_t *state, void *user_data) {
print("rs\n");
active_tapdances[TD_LVL0_TKR2] = 0;
  switch (xtap_state.state) {
    case SINGLE_HOLD_INT: unregister_code(KC_LCTRL); break;//print("Unhandled singled hold int rs\n"); break;
    case SINGLE_TAP: unregister_code(KC_COMMA); unregister_code(KC_LSHIFT);break;
    case DOUBLE_TAP: unregister_code(KC_COMMA); unregister_code(KC_LSHIFT);break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    //case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  xtap_state.state = 0;
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
  [TD_CMD_C]  = ACTION_TAP_DANCE_DOUBLE(KC_C, LGUI(KC_C)),
  [TD_CMD_V]  = ACTION_TAP_DANCE_DOUBLE(KC_V, LGUI(KC_V)),
  [TD_CMD_Z]  = ACTION_TAP_DANCE_DOUBLE(KC_Z, LGUI(KC_Z)),
  [TD_CMD_X]  = ACTION_TAP_DANCE_DOUBLE(KC_X, LGUI(KC_X)),
  [TD_PG_UP_HOME]  = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
  [TD_PG_DOWN_END]  = ACTION_TAP_DANCE_DOUBLE(KC_PGDOWN, KC_END),
  [TD_DBL_OR_SINGLE_QUOTE] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_2), KC_DK_SINGLE_QUOTE),
  [TD_SIGNLE_QUOTE_OR_ASTERIX] = ACTION_TAP_DANCE_DOUBLE(KC_DK_SINGLE_QUOTE, LSFT(KC_DK_SINGLE_QUOTE)),
  [TD_a_A]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset),
  [TD_LAY1_OR_3]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset),
  [TD_LVL0_TKR2]     = ACTION_TAP_DANCE_FN_ADVANCED(td_lvl0_tkr2_always,td_lvl0_tkr2_finished, td_lvl0_tkr2_reset)
// Other declarations would go here, separated by commas, if you have them
};
