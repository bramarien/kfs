#include "keyboard.h"

// the key associated with each code with shift down and with shift up
static const char	us_keymap[][2] = {
	{'\0', '\0'}, {SK_ESCAPE, SK_ESCAPE}, {'1', '!'}, {'2', '@'},
	{'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'},
	{'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'},
	{'-', '_'}, {'=', '+'}, {SK_BACKSPACE, SK_BACKSPACE}, {'\t', '\t'},
	{'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'},
	{'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'},
	{'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'},
	{'\n', '\n'}, {SK_CTRL_L, SK_CTRL_L}, {'a', 'A'}, {'s', 'S'},
	{'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'},
	{'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'},
	{'\'', '"'}, {'`', '~'}, {SK_SHIFT_L, SK_SHIFT_L}, {'\\', '|'},
	{'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'},
	{'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'},
	{'.', '>'}, {'/', '?'}, {SK_SHIFT_R, SK_SHIFT_R}, {'*', SK_PRINT_SCREEN},
	{SK_ALT_L, SK_ALT_L}, {' ', ' '}, {SK_CAPS_LOCK, SK_CAPS_LOCK},
	{SK_F1, SK_F1}, {SK_F2, SK_F2}, {SK_F3, SK_F3}, {SK_F4, SK_F4}, {SK_F5, SK_F5},
	{SK_F6, SK_F6}, {SK_F7, SK_F7}, {SK_F8, SK_F8}, {SK_F9, SK_F9}, {SK_F10, SK_F10},
	{SK_NUM_LOCK, SK_NUM_LOCK}, {SK_SCROLL_LOCK, SK_SCROLL_LOCK}, {'7', SK_HOME},
	{'8', SK_UP}, {'9', SK_PAGE_UP}, {'-', '-'}, {'4', SK_LEFT},
	{'5', '5'}, {'6', SK_RIGHT}, {'+', '+'}, {'1', SK_END},
	{'2', SK_DOWN}, {'3', SK_PAGE_DOWN}, {'0', SK_INSERT},
	{'.', SK_DELETE}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'},
	{SK_F11, SK_F11}, {SK_F12, SK_F12}, {'\0', '\0'}, {'\0', '\0'},
	{'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'},
	{'\n', '\n'}, {SK_CTRL_R, SK_CTRL_R}, {'/', '/'}, {SK_PRTSCR, SK_PRTSCR},
	{SK_ALT_R, SK_ALT_R}, {'\0', '\0'}, {SK_HOME, SK_HOME}, {SK_UP, SK_UP},
	{SK_PAGE_UP, SK_PAGE_UP}, {SK_LEFT, SK_LEFT}, {SK_RIGHT, SK_RIGHT},
	{SK_END, SK_END}, {SK_DOWN, SK_DOWN}, {SK_PAGE_DOWN, SK_PAGE_DOWN},
	{SK_INSERT, SK_INSERT}, {SK_DELETE, SK_DELETE}, {'\0', '\0'}, {'\0', '\0'},
	{'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'},
	{SK_PAUSE, SK_PAUSE}
};

char	get_keystroke(void) {
	uint8_t		code;
	char		key;
	// static bool	shift = 0;

	while (true) {
		code = get_scan_code();
		if (code == 0xE0) {
			get_scan_code();
		} else if (code == 0xE1) {
			get_scan_code();
			get_scan_code();
		} else if (code < sizeof(us_keymap) / 2){
			key = us_keymap[code][0];
			if (key > 0)
				break;
		}
	}
	return (key);
}
