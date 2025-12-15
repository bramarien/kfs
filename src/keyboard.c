#include "keyboard.h"
#include <limits.h>

// the key associated with each code with shift down and with shift up
// static const char	us_keymap[][2] = {
// 	{'\0', '\0'}, {SK_ESCAPE, SK_ESCAPE}, {'1', '!'}, {'2', '@'},
// 	{'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'},
// 	{'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'},
// 	{'-', '_'}, {'=', '+'}, {SK_BACKSPACE, SK_BACKSPACE}, {'\t', '\t'},
// 	{'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'},
// 	{'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'},
// 	{'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'},
// 	{'\n', '\n'}, {SK_CTRL_L, SK_CTRL_L}, {'a', 'A'}, {'s', 'S'},
// 	{'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'},
// 	{'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'},
// 	{'\'', '"'}, {'`', '~'}, {SK_SHIFT_L, SK_SHIFT_L}, {'\\', '|'},
// 	{'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'},
// 	{'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'},
// 	{'.', '>'}, {'/', '?'}, {SK_SHIFT_R, SK_SHIFT_R}, {'*', SK_PRINT_SCREEN},
// 	{SK_ALT_L, SK_ALT_L}, {' ', ' '}, {SK_CAPS_LOCK, SK_CAPS_LOCK},
// 	{SK_F1, SK_F1}, {SK_F2, SK_F2}, {SK_F3, SK_F3}, {SK_F4, SK_F4}, {SK_F5, SK_F5},
// 	{SK_F6, SK_F6}, {SK_F7, SK_F7}, {SK_F8, SK_F8}, {SK_F9, SK_F9}, {SK_F10, SK_F10},
// 	{SK_NUM_LOCK, SK_NUM_LOCK}, {SK_SCROLL_LOCK, SK_SCROLL_LOCK}, {'7', SK_HOME},
// 	{'8', SK_UP}, {'9', SK_PAGE_UP}, {'-', '-'}, {'4', SK_LEFT},
// 	{'5', '5'}, {'6', SK_RIGHT}, {'+', '+'}, {'1', SK_END},
// 	{'2', SK_DOWN}, {'3', SK_PAGE_DOWN}, {'0', SK_INSERT},
// 	{'.', SK_DELETE}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'},
// 	{SK_F11, SK_F11}, {SK_F12, SK_F12}, {'\0', '\0'}, {'\0', '\0'},
// 	{'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'},
// 	{'\n', '\n'}, {SK_CTRL_R, SK_CTRL_R}, {'/', '/'}, {SK_PRTSCR, SK_PRTSCR},
// 	{SK_ALT_R, SK_ALT_R}, {'\0', '\0'}, {SK_HOME, SK_HOME}, {SK_UP, SK_UP},
// 	{SK_PAGE_UP, SK_PAGE_UP}, {SK_LEFT, SK_LEFT}, {SK_RIGHT, SK_RIGHT},
// 	{SK_END, SK_END}, {SK_DOWN, SK_DOWN}, {SK_PAGE_DOWN, SK_PAGE_DOWN},
// 	{SK_INSERT, SK_INSERT}, {SK_DELETE, SK_DELETE}, {'\0', '\0'}, {'\0', '\0'},
// 	{'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'},
// 	{SK_PAUSE, SK_PAUSE}
// };

// keyboard layout used for the creation of the scancode map:
// row 0: ESC  F1  F2  F3  F4  F5  F6  F7  F8  F9  F10  F11  F12  PRSC  SCRL  PAUSE
// row 1: `  1  2  3  4  5  6  7  8  9  0  -  =  BS  INS  HOME  PGUP  NUML  KP_/  KP_*  KP_-
// row 2: TAB  Q  W  E  R  T  Y  U  I  O  P  [  ]  \  DEL  END  PGDN  KP_7  KP_8  KP_9  KP_+
// row 3: CAPS  A  S  D  F  G  H  J  K  L  ;  '  ENTER  KP_4  KP_5  KP_6
// row 4: LSHIFT  Z  X  C  V  B  N  M  ,  .  /  RSHIFT  UP  KP_1  KP_2  KP_3  KP_ENTER
// row 5: LCTRL  LWIN  LALT  SPACE  RALT  RWIN  MENU  RCTRL  LEFT  DOWN  RIGHT  KP_0  KP_.
// all the remaining keys (media for exemple) are placed on rows 6 and 7 (haha)
// ^^^ not implemented yet because flemme

// Maps PS/2 Set 1 scancodes to logical key positions (row/column) based on the
// visible ANSI full-size keyboard layout (first part).
static const uint8_t scanmap[] = {
	[0x01] = POS_KEY(0, 0),	// ESC

	[0x02] = POS_KEY(1, 1),	// 1
	[0x03] = POS_KEY(1, 2),	// 2
	[0x04] = POS_KEY(1, 3),	// 3
	[0x05] = POS_KEY(1, 4),	// 4
	[0x06] = POS_KEY(1, 5),	// 5
	[0x07] = POS_KEY(1, 6),	// 6
	[0x08] = POS_KEY(1, 7),	// 7
	[0x09] = POS_KEY(1, 8),	// 8
	[0x0A] = POS_KEY(1, 9),	// 9
	[0x0B] = POS_KEY(1,10),	// 0
	[0x0C] = POS_KEY(1,11),	// -
	[0x0D] = POS_KEY(1,12),	// =
	[0x0E] = POS_KEY(1,13),	// Backspace

	[0x0F] = POS_KEY(2, 0),	// Tab
	[0x10] = POS_KEY(2, 1),	// Q
	[0x11] = POS_KEY(2, 2),	// W
	[0x12] = POS_KEY(2, 3),	// E
	[0x13] = POS_KEY(2, 4),	// R
	[0x14] = POS_KEY(2, 5),	// T
	[0x15] = POS_KEY(2, 6),	// Y
	[0x16] = POS_KEY(2, 7),	// U
	[0x17] = POS_KEY(2, 8),	// I
	[0x18] = POS_KEY(2, 9),	// O
	[0x19] = POS_KEY(2,10),	// P
	[0x1A] = POS_KEY(2,11),	// [
	[0x1B] = POS_KEY(2,12),	// ]
	[0x2B] = POS_KEY(2,13),	// Backslash

	[0x1C] = POS_KEY(3,12),	// Enter
	[0x1D] = POS_KEY(5, 0),	// Left Ctrl

	[0x1E] = POS_KEY(3, 1),	// A
	[0x1F] = POS_KEY(3, 2),	// S
	[0x20] = POS_KEY(3, 3),	// D
	[0x21] = POS_KEY(3, 4),	// F
	[0x22] = POS_KEY(3, 5),	// G
	[0x23] = POS_KEY(3, 6),	// H
	[0x24] = POS_KEY(3, 7),	// J
	[0x25] = POS_KEY(3, 8),	// K
	[0x26] = POS_KEY(3, 9),	// L
	[0x27] = POS_KEY(3,10),	// ;
	[0x28] = POS_KEY(3,11),	// '

	[0x29] = POS_KEY(1, 0),	// `
	[0x2A] = POS_KEY(4, 0),	// Left Shift
	[0x2C] = POS_KEY(4, 1),	// Z
	[0x2D] = POS_KEY(4, 2),	// X
	[0x2E] = POS_KEY(4, 3),	// C
	[0x2F] = POS_KEY(4, 4),	// V
	[0x30] = POS_KEY(4, 5),	// B
	[0x31] = POS_KEY(4, 6),	// N
	[0x32] = POS_KEY(4, 7),	// M
	[0x33] = POS_KEY(4, 8),	// ,
	[0x34] = POS_KEY(4, 9),	// .
	[0x35] = POS_KEY(4,10),	// /
	[0x36] = POS_KEY(4,11),	// Right Shift

	[0x37] = POS_KEY(1,19),	// Keypad *
	[0x38] = POS_KEY(5, 2),	// Left Alt
	[0x39] = POS_KEY(5, 3),	// Space
	[0x3A] = POS_KEY(3, 0),	// CapsLock

	[0x3B] = POS_KEY(0, 1),	// F1
	[0x3C] = POS_KEY(0, 2),	// F2
	[0x3D] = POS_KEY(0, 3),	// F3
	[0x3E] = POS_KEY(0, 4),	// F4
	[0x3F] = POS_KEY(0, 5),	// F5
	[0x40] = POS_KEY(0, 6),	// F6
	[0x41] = POS_KEY(0, 7),	// F7
	[0x42] = POS_KEY(0, 8),	// F8
	[0x43] = POS_KEY(0, 9),	// F9
	[0x44] = POS_KEY(0,10),	// F10
	[0x57] = POS_KEY(0,11),	// F11
	[0x58] = POS_KEY(0,12),	// F12

	[0x45] = POS_KEY(1,17),	// NumLock
	[0x46] = POS_KEY(0,14),	// ScrollLock

	[0x47] = POS_KEY(2,17),	// Keypad 7
	[0x48] = POS_KEY(2,18),	// Keypad 8
	[0x49] = POS_KEY(2,19),	// Keypad 9
	[0x4A] = POS_KEY(1,20),	// Keypad -
	[0x4B] = POS_KEY(3,13),	// Keypad 4
	[0x4C] = POS_KEY(3,14),	// Keypad 5
	[0x4D] = POS_KEY(3,15),	// Keypad 6
	[0x4E] = POS_KEY(2,20),	// Keypad +
	[0x4F] = POS_KEY(4,13),	// Keypad 1
	[0x50] = POS_KEY(4,14),	// Keypad 2
	[0x51] = POS_KEY(4,15),	// Keypad 3
	[0x52] = POS_KEY(5,11),	// Keypad 0
	[0x53] = POS_KEY(5,12),	// Keypad .
};

// second scanmap for extended scancode (0xE0)
static const uint8_t scanmap_ext[] = {
	[0x1C] = POS_KEY(4,16),	// Keypad Enter
	[0x1D] = POS_KEY(5, 7),	// Right control
	[0x35] = POS_KEY(1,18),	// Keypad /
	[0x38] = POS_KEY(5, 4),	// Right alt (or altGr)
	[0x47] = POS_KEY(1,15),	// Home
	[0x49] = POS_KEY(1,16),	// Page up
	[0x4F] = POS_KEY(2,15),	// End
	[0x51] = POS_KEY(2,16),	// Page down
	[0x52] = POS_KEY(1,14),	// Insert
	[0x53] = POS_KEY(2,14),	// Delete
	[0x48] = POS_KEY(4,12),	// Arrow up
	[0x4B] = POS_KEY(5, 8),	// Arrow left
	[0x4D] = POS_KEY(5,10),	// Arrow right
	[0x50] = POS_KEY(5, 9),	// Arrow down
	[0x2A] = POS_KEY(0,13),	// Print screen
	[0x5B] = POS_KEY(5, 1),	// Left super
	[0x5C] = POS_KEY(5, 5),	// Right super
	[0x5D] = POS_KEY(5, 6),	// "apps"
	[0x10] = POS_KEY(6, 0),	// Multimedia previous track
	[0x19] = POS_KEY(6, 1),	// Multimedia next track
	[0x20] = POS_KEY(6, 3),	// Multimedia mute
	[0x21] = POS_KEY(6, 4),	// Multimedia calculator
	[0x22] = POS_KEY(6, 5),	// Multimedia play
	[0x24] = POS_KEY(6, 6),	// Multimedia stop
	[0x2E] = POS_KEY(6, 7),	// Multimedia volume down
	[0x30] = POS_KEY(6, 8),	// Multimedia volume up
	[0x32] = POS_KEY(6, 9),	// Multimedia WWW home
	[0x5E] = POS_KEY(6,10),	// ACPI power
	[0x5F] = POS_KEY(6,11),	// ACPI sleep
	[0x63] = POS_KEY(6,12),	// ACPI wake
	[0x65] = POS_KEY(6,13),	// Multimedia WWW search
	[0x66] = POS_KEY(6,14),	// Multimedia WWW favorites
	[0x67] = POS_KEY(6,15),	// Multimedia WWW refresh
	[0x68] = POS_KEY(7, 0),	// Multimedia WWW stop
	[0x69] = POS_KEY(7, 1),	// Multimedia WWW forward
	[0x6A] = POS_KEY(7, 2),	// Multimedia WWW back
	[0x6B] = POS_KEY(7, 3),	// Multimedia my computer
	[0x6C] = POS_KEY(7, 4),	// Multimedia email
	[0x6D] = POS_KEY(7, 5),	// Multimedia media select
};

static const char	keymap_us_ansi[][2] = {
	[POS_KEY(1, 1)] = {'1', '!'},	// 1
	[POS_KEY(1, 2)] = {'2', '@'},	// 2
	[POS_KEY(1, 3)] = {'3', '#'},	// 3
	[POS_KEY(1, 4)] = {'4', '$'},	// 4
	[POS_KEY(1, 5)] = {'5', '%'},	// 5
	[POS_KEY(1, 6)] = {'6', '^'},	// 6
	[POS_KEY(1, 7)] = {'7', '&'},	// 7
	[POS_KEY(1, 8)] = {'8', '*'},	// 8
	[POS_KEY(1, 9)] = {'9', '('},	// 9
	[POS_KEY(1,10)] = {'0', ')'},	// 0
	[POS_KEY(1,11)] = {'-', '_'},	// -
	[POS_KEY(1,12)] = {'=', '+'},	// =
	[POS_KEY(1,13)] = {'\b', '\b'},	// Backspace
	[POS_KEY(2, 0)] = {'\t', '\t'},	// Tab
	[POS_KEY(2, 1)] = {'q', 'Q'},	// Q
	[POS_KEY(2, 2)] = {'w', 'W'},	// W
	[POS_KEY(2, 3)] = {'e', 'E'},	// E
	[POS_KEY(2, 4)] = {'r', 'R'},	// R
	[POS_KEY(2, 5)] = {'t', 'T'},	// T
	[POS_KEY(2, 6)] = {'y', 'Y'},	// Y
	[POS_KEY(2, 7)] = {'u', 'U'},	// U
	[POS_KEY(2, 8)] = {'i', 'I'},	// I
	[POS_KEY(2, 9)] = {'o', 'O'},	// O
	[POS_KEY(2,10)] = {'p', 'P'},	// P
	[POS_KEY(2,11)] = {'[', '{'},	// [
	[POS_KEY(2,12)] = {']', '}'},	// ]
	[POS_KEY(2,13)] = {'\\', '|'},	// Backslash
	[POS_KEY(3,12)] = {'\n', '\n'},	// Enter
	[POS_KEY(5, 0)] = {KEY_L_CTRL, KEY_L_CTRL},	// Left Ctrl
	[POS_KEY(3, 1)] = {'a', 'A'},	// A
	[POS_KEY(3, 2)] = {'s', 'S'},	// S
	[POS_KEY(3, 3)] = {'d', 'D'},	// D
	[POS_KEY(3, 4)] = {'f', 'F'},	// F
	[POS_KEY(3, 5)] = {'g', 'G'},	// G
	[POS_KEY(3, 6)] = {'h', 'H'},	// H
	[POS_KEY(3, 7)] = {'j', 'J'},	// J
	[POS_KEY(3, 8)] = {'k', 'K'},	// K
	[POS_KEY(3, 9)] = {'l', 'L'},	// L
	[POS_KEY(3,10)] = {';', ':'},	// ;
	[POS_KEY(3,11)] = {'\'', '"'},	// '
	[POS_KEY(1, 0)] = {'`', '~'},	// `
	[POS_KEY(4, 0)] = {KEY_L_SHIFT, KEY_L_SHIFT},	// Left Shift
	[POS_KEY(4, 1)] = {'z', 'Z'},	// Z
	[POS_KEY(4, 2)] = {'x', 'X'},	// X
	[POS_KEY(4, 3)] = {'c', 'C'},	// C
	[POS_KEY(4, 4)] = {'v', 'V'},	// V
	[POS_KEY(4, 5)] = {'b', 'B'},	// B
	[POS_KEY(4, 6)] = {'n', 'N'},	// N
	[POS_KEY(4, 7)] = {'m', 'M'},	// M
	[POS_KEY(4, 8)] = {',', '<'},	// ,
	[POS_KEY(4, 9)] = {'.', '>'},	// .
	[POS_KEY(4,10)] = {'/', '?'},	// /
	[POS_KEY(4,11)] = {KEY_R_SHIFT, KEY_R_SHIFT},	// Right Shift
	[POS_KEY(1,19)] = {'*', '*'},	// Keypad *
	[POS_KEY(5, 2)] = {KEY_L_ALT, KEY_L_ALT},	// Left Alt
	[POS_KEY(5, 3)] = {' ', ' '},	// Space
	[POS_KEY(3, 0)] = {KEY_CAPS_LOCK, KEY_CAPS_LOCK},	// CapsLock
	[POS_KEY(0, 0)] = {KEY_ESCAPE, KEY_ESCAPE},	// F1
	[POS_KEY(0, 1)] = {KEY_F1, KEY_F1},	// F1
	[POS_KEY(0, 2)] = {KEY_F2, KEY_F2},	// F2
	[POS_KEY(0, 3)] = {KEY_F3, KEY_F3},	// F3
	[POS_KEY(0, 4)] = {KEY_F4, KEY_F4},	// F4
	[POS_KEY(0, 5)] = {KEY_F5, KEY_F5},	// F5
	[POS_KEY(0, 6)] = {KEY_F6, KEY_F6},	// F6
	[POS_KEY(0, 7)] = {KEY_F7, KEY_F7},	// F7
	[POS_KEY(0, 8)] = {KEY_F8, KEY_F8},	// F8
	[POS_KEY(0, 9)] = {KEY_F9, KEY_F9},	// F9
	[POS_KEY(0,10)] = {KEY_F10, KEY_F10},	// F10
	[POS_KEY(0,11)] = {KEY_F11, KEY_F11},	// F11
	[POS_KEY(0,12)] = {KEY_F12, KEY_F12},	// F12
	[POS_KEY(1,17)] = {KEY_NUM_LOCK, KEY_NUM_LOCK},	// NumLock
	[POS_KEY(0,14)] = {KEY_SCROLL_LOCK, KEY_SCROLL_LOCK},	// ScrollLock
	[POS_KEY(0,15)] = {KEY_PAUSE, KEY_PAUSE}, // Pause
	[POS_KEY(2,17)] = {'7', KEY_HOME},	// Keypad 7
	[POS_KEY(2,18)] = {'8', KEY_ARROW_UP},	// Keypad 8
	[POS_KEY(2,19)] = {'9', KEY_PAGE_UP},	// Keypad 9
	[POS_KEY(1,20)] = {'-', '-'},	// Keypad -
	[POS_KEY(3,13)] = {'4', KEY_ARROW_RIGHT},	// Keypad 4
	[POS_KEY(3,14)] = {'5', '5'},	// Keypad 5
	[POS_KEY(3,15)] = {'6', KEY_ARROW_RIGHT},	// Keypad 6
	[POS_KEY(2,20)] = {'+', '+'},	// Keypad +
	[POS_KEY(4,13)] = {'1', KEY_END},	// Keypad 1
	[POS_KEY(4,14)] = {'2', KEY_ARROW_DOWN},	// Keypad 2
	[POS_KEY(4,15)] = {'3', KEY_PAGE_DOWN},	// Keypad 3
	[POS_KEY(5,11)] = {'0', KEY_INSERT},	// Keypad 0
	[POS_KEY(5,12)] = {'.', KEY_DELETE},	// Keypad .
	[POS_KEY(4,16)] = {'\n', '\n'},	// Keypad Enter
	[POS_KEY(5, 7)] = {KEY_R_CTRL, KEY_R_CTRL},	// Right control
	[POS_KEY(1,18)] = {'/', '/'},	// Keypad /
	[POS_KEY(5, 4)] = {KEY_R_ALT, KEY_R_ALT},	// Right alt (or altGr)
	[POS_KEY(1,15)] = {KEY_HOME, KEY_HOME},	// Home
	[POS_KEY(1,16)] = {KEY_PAGE_UP, KEY_PAGE_UP},	// Page up
	[POS_KEY(2,15)] = {KEY_END, KEY_END},	// End
	[POS_KEY(2,16)] = {KEY_PAGE_DOWN, KEY_PAGE_DOWN},	// Page down
	[POS_KEY(1,14)] = {KEY_INSERT, KEY_INSERT},	// Insert
	[POS_KEY(2,14)] = {127, 127},	// Delete
	[POS_KEY(4,12)] = {KEY_ARROW_UP, KEY_ARROW_UP},	// Arrow up
	[POS_KEY(5, 8)] = {KEY_ARROW_LEFT, KEY_ARROW_LEFT},	// Arrow left
	[POS_KEY(5,10)] = {KEY_ARROW_RIGHT, KEY_ARROW_RIGHT},	// Arrow right
	[POS_KEY(5, 9)] = {KEY_ARROW_DOWN, KEY_ARROW_DOWN},	// Arrow down
	[POS_KEY(0,13)] = {KEY_PRINT_SCREEN, KEY_PRINT_SCREEN},	// Print screen
	[POS_KEY(5, 1)] = {KEY_LEFT_SUPER, KEY_LEFT_SUPER},	// Left super
	[POS_KEY(5, 5)] = {KEY_RIGHT_SUPER, KEY_RIGHT_SUPER},	// Right super
	[POS_KEY(5, 6)] = {KEY_APPS, KEY_APPS},	// "apps"
	[POS_KEY(6, 0)] = {KEY_MEDIA_PREV_TRACK, KEY_MEDIA_PREV_TRACK},	// Multimedia previous track
	[POS_KEY(6, 1)] = {KEY_MEDIA_NEXT_TRACK, KEY_MEDIA_NEXT_TRACK},	// Multimedia next track
	[POS_KEY(6, 3)] = {KEY_MEDIA_MUTE, KEY_MEDIA_MUTE},	// Multimedia mute
	[POS_KEY(6, 4)] = {KEY_MEDIA_CALCULATOR, KEY_MEDIA_CALCULATOR},	// Multimedia calculator
	[POS_KEY(6, 5)] = {KEY_MEDIA_PLAY, KEY_MEDIA_PLAY},	// Multimedia play
	[POS_KEY(6, 6)] = {KEY_MEDIA_STOP, KEY_MEDIA_STOP},	// Multimedia stop
	[POS_KEY(6, 7)] = {KEY_MEDIA_VOLUME_DOWN, KEY_MEDIA_VOLUME_DOWN},	// Multimedia volume down
	[POS_KEY(6, 8)] = {KEY_MEDIA_VOLUME_UP, KEY_MEDIA_VOLUME_UP},	// Multimedia volume up
	[POS_KEY(6, 9)] = {KEY_MEDIA_WWW_HOME, KEY_MEDIA_WWW_HOME},	// Multimedia WWW home
	[POS_KEY(6,10)] = {KEY_ACPI_POWER, KEY_ACPI_POWER},	// ACPI power
	[POS_KEY(6,11)] = {KEY_ACPI_SLEEP, KEY_ACPI_SLEEP},	// ACPI sleep
	[POS_KEY(6,12)] = {KEY_ACPI_WAKE, KEY_ACPI_WAKE},	// ACPI wake
	[POS_KEY(6,13)] = {KEY_MEDIA_WWW_SEARCH, KEY_MEDIA_WWW_SEARCH},	// Multimedia WWW search
	[POS_KEY(6,14)] = {KEY_MEDIA_WWW_FAVORITES, KEY_MEDIA_WWW_FAVORITES},	// Multimedia WWW favorites
	[POS_KEY(6,15)] = {KEY_MEDIA_WWW_REFRESH, KEY_MEDIA_WWW_REFRESH},	// Multimedia WWW refresh
	[POS_KEY(7, 0)] = {KEY_MEDIA_WWW_STOP, KEY_MEDIA_WWW_STOP},	// Multimedia WWW stop
	[POS_KEY(7, 1)] = {KEY_MEDIA_WWW_FORWARD, KEY_MEDIA_WWW_FORWARD},	// Multimedia WWW forward
	[POS_KEY(7, 2)] = {KEY_MEDIA_WWW_BACK, KEY_MEDIA_WWW_BACK},	// Multimedia WWW back
	[POS_KEY(7, 3)] = {KEY_MEDIA_MY_COMPUTER, KEY_MEDIA_MY_COMPUTER},	// Multimedia my computer
	[POS_KEY(7, 4)] = {KEY_MEDIA_EMAIL, KEY_MEDIA_EMAIL},	// Multimedia email
	[POS_KEY(7, 5)] = {KEY_MEDIA_SELECT, KEY_MEDIA_SELECT},	// Multimedia media select
};

struct input_event	get_input_event(void) {
	uint8_t				code;
	bool				extended;
	struct input_event	event;

	while (true) {
		extended = false;
		event.pressed = true;
		code = get_scan_code();
		// Pause key starts with 0xE1, it's the only one
		if (code == 0xE1) {
			get_scan_code();
			get_scan_code();
			get_scan_code();
			get_scan_code();
			get_scan_code();
			event.keycode = POS_KEY(0,15);
			break;
		}
		if (code == 0xE0) {
			extended = true;
			code = get_scan_code();
		}
		if (code >= 0x80) {
			event.pressed = false;
			code -= 0x80;
		}
		if (extended) {
			if (code >= sizeof(scanmap_ext))
				continue;
			event.keycode = scanmap_ext[code];
		}
		else {
			if (code >= sizeof(scanmap))
				continue;
			event.keycode = scanmap[code];
		}
		break;
	}
	return (event);
}

char	get_keypress(void) {
	struct input_event	event;
	static bool			l_shift_pressed = false;
	static bool			r_shift_pressed = false;
	static bool			caps_locked = false;
	static bool			caps_alternator = false;
	char				key;

	while (true) {
		event = get_input_event();
		key = keymap_us_ansi[event.keycode][l_shift_pressed | r_shift_pressed | caps_locked];
		if (key == KEY_L_SHIFT) {
			if (event.pressed)
				l_shift_pressed = 1;
			else
				l_shift_pressed = 0;
		} else if (key == KEY_R_SHIFT) {
			if (event.pressed)
				r_shift_pressed = 1;
			else
				r_shift_pressed = 0;
		} else if (key == KEY_CAPS_LOCK) {
			if (event.pressed) {
					caps_locked = true;
			} else {
				if (caps_alternator)
					caps_locked = false;
				caps_alternator = !caps_alternator;
			}
		} else if (key >= 0 && event.pressed)
			return (key);
	}
}

