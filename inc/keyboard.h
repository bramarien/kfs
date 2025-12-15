#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// the 3 highest bits are the row and the 5 lowest are the column
// together they indicate the position of the key on the keyboard (when you look at it)
#define POS_KEY(row, col) ((uint8_t) ((row << 5) | col))

#define KEY_L_SHIFT -1
#define KEY_R_SHIFT -2
#define KEY_L_CTRL -3
#define KEY_R_CTRL -4
#define KEY_CAPS_LOCK -5
#define KEY_NUM_LOCK -6
#define KEY_F1 -7
#define KEY_F2 -8
#define KEY_F3 -9
#define KEY_F4 -10
#define KEY_F5 -11
#define KEY_F6 -12
#define KEY_F7 -13
#define KEY_F8 -14
#define KEY_F9 -15
#define KEY_F10 -16
#define KEY_F11 -17
#define KEY_F12 -18
#define KEY_L_ALT -19
#define KEY_R_ALT -20
#define KEY_SCROLL_LOCK -21
#define KEY_HOME -22
#define KEY_END -23
#define KEY_INSERT -24
#define KEY_DELETE -25
#define KEY_PAGE_UP -26
#define KEY_PAGE_DOWN -27
#define KEY_PRINT_SCREEN -28
#define KEY_ARROW_UP -29
#define KEY_ARROW_LEFT -30
#define KEY_ARROW_RIGHT -31
#define KEY_ARROW_DOWN -32
#define KEY_LEFT_SUPER -33
#define KEY_RIGHT_SUPER -34
#define KEY_APPS -35
#define KEY_MEDIA_PREV_TRACK -36
#define KEY_MEDIA_NEXT_TRACK -37
#define KEY_MEDIA_MUTE -38
#define KEY_MEDIA_CALCULATOR -39
#define KEY_MEDIA_PLAY -40
#define KEY_MEDIA_STOP -41
#define KEY_MEDIA_VOLUME_DOWN -42
#define KEY_MEDIA_VOLUME_UP -43
#define KEY_MEDIA_WWW_HOME -44
#define KEY_ACPI_POWER -45
#define KEY_ACPI_SLEEP -46
#define KEY_ACPI_WAKE -47
#define KEY_MEDIA_WWW_SEARCH -48
#define KEY_MEDIA_WWW_FAVORITES -49
#define KEY_MEDIA_WWW_REFRESH -50
#define KEY_MEDIA_WWW_STOP -51
#define KEY_MEDIA_WWW_FORWARD -52
#define KEY_MEDIA_WWW_BACK -53
#define KEY_MEDIA_MY_COMPUTER -54
#define KEY_MEDIA_EMAIL -55
#define KEY_MEDIA_SELECT -56
#define KEY_ESCAPE -57
#define KEY_PAUSE -58

struct input_event {
	uint8_t	keycode;
	bool	pressed;
};

extern uint8_t		get_scan_code(void);
struct input_event	get_keyboard_event(void);
char				get_keypress(void);
