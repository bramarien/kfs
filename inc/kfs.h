#pragma once

#include <stddef.h>
#include <stdint.h>
#include "multiboot2.h"

#define PSF1_FONT_MAGIC 0x0436
#define VGA_ADDR 0xB8000

struct font; // forward declaration

extern char _binary_fonts_unifont_apl8x16_psf_start[];
extern char _binary_fonts_unifont_apl8x16_psf_end[];

struct kfs {	
	struct multiboot_tag_framebuffer *tag_fb;
	// void *fb = (void *) (unsigned long) tag_fb->common.framebuffer_addr;
	struct font *main_font;
};