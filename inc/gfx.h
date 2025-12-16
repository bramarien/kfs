#pragma once

#include "stdint.h"

struct kfs;
struct multiboot_tag_framebuffer;

typedef struct {
	uint16_t magic; // Magic bytes for identification.
	uint8_t fontMode; // PSF font mode.
	uint8_t characterSize; // PSF character size.
} PSF1_Header;

// Struct for font using psf1 header
struct font {
	PSF1_Header *header;
	char *glyphs;
};

void putpixel(struct multiboot_tag_framebuffer *fb, uint32_t x, uint32_t y, uint32_t color);
void fb_putchar(struct multiboot_tag_framebuffer *fb, struct font *f, uint32_t x, uint32_t y, uint32_t color, char c);