#include "console.h"


static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;


void console_write_char(struct multiboot_tag_framebuffer *fb, struct font *f, uint32_t color, char c)
{
	uint32_t char_w = 8;
	uint32_t char_h = f->header->characterSize;
	uint32_t fb_w   = fb->common.framebuffer_width;

	if ((uint16_t)c == 255) {
		fb_putchar(fb, f, cursor_x - 1, cursor_y, 0x00000000, 0);
	}
	else if (c == '\n') {
		cursor_x = 0;
		cursor_y += char_h;
		return;
	}

	fb_putchar(fb, f, cursor_x, cursor_y, color, c);

	cursor_x += char_w;

	if (cursor_x + char_w > fb_w) {
		cursor_x = 0;
		cursor_y += char_h;
	}
}

void console_write(struct multiboot_tag_framebuffer *fb, struct font *f, uint32_t color, const char *s)
{
    while (*s) {
        console_write_char(fb, f, color, *s);
        s++;
    }
}

void console_write_hex(struct multiboot_tag_framebuffer *fb, struct font *f, uint32_t color, uint64_t value)
{
	char buf[2 + 16 + 1];
	int i = 0;

	buf[i++] = '0';
	buf[i++] = 'x';

	int started = 0;

	for (int shift = 60; shift >= 0; shift -= 4) {
		uint8_t nibble = (value >> shift) & 0xF;

		if (nibble || started || shift == 0) {
			started = 1;
			buf[i++] = (nibble < 10)
			? ('0' + nibble)
			: ('A' + nibble - 10);
		}
	}

	buf[i] = '\0';

	console_write(fb, f, color, buf);
}

static inline uint32_t read_sp(void)
{
    uint32_t sp;
    __asm__ volatile ("mov %%esp, %0" : "=r"(sp));
    return sp;
}

void console_dump_stack(struct multiboot_tag_framebuffer *fb, struct font *f, uint32_t color, uint32_t count)
{
    uint32_t *sp = (uint32_t *)read_sp();

    console_write(fb, f, color, "Stack dump:\n");

    for (uint32_t i = 0; i < count; i++) {
        console_write_hex(fb, f, color, (uint32_t)&sp[i]);
        console_write(fb, f, color, ": ");
        console_write_hex(fb, f, color, sp[i]);
        console_write(fb, f, color, "\n");
    }
}
