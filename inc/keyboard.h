#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// special keys have a negative code and printable have a positive
#define SK_ESCAPE -1
#define SK_BACKSPACE -2
#define SK_CTRL_L -3
#define SK_CTRL_R -4
#define SK_SHIFT_L -5
#define SK_SHIFT_R -6
#define SK_PRINT_SCREEN -7
#define SK_ALT_L -8
#define SK_ALT_R -9
#define SK_CAPS_LOCK -10
#define SK_NUM_LOCK -11
#define SK_SCROLL_LOCK -12
#define SK_F1 -13
#define SK_F2 -14
#define SK_F3 -15
#define SK_F4 -16
#define SK_F5 -17
#define SK_F6 -18
#define SK_F7 -19
#define SK_F8 -20
#define SK_F9 -21
#define SK_F10 -22
#define SK_F11 -23
#define SK_F12 -24
#define SK_UP -25
#define SK_LEFT -26
#define SK_RIGHT -27
#define SK_DOWN -28
#define SK_INSERT -29
#define SK_DELETE -30
#define SK_HOME -31
#define SK_END -32
#define SK_PAGE_UP -33
#define SK_PAGE_DOWN -34
#define SK_PRTSCR -35
#define SK_PAUSE -36

extern uint8_t	get_scan_code(void);
char			get_keystroke(void);
