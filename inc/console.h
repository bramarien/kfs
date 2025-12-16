#pragma once

#include "kfs.h"
#include "gfx.h"

void console_write_char(struct multiboot_tag_framebuffer *fb, struct font *f, uint32_t color, char c);
void console_write(struct multiboot_tag_framebuffer *fb, struct font *f, uint32_t color, const char *s);
void console_write_hex(struct multiboot_tag_framebuffer *fb, struct font *f, uint32_t color, uint64_t value);
void console_dump_stack(struct multiboot_tag_framebuffer *fb, struct font *f, uint32_t color, uint32_t count);