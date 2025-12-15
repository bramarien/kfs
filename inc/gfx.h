#pragma once

#include "stdint.h"

struct kfs;

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

void fb_putchar(struct kfs *kfs, struct font *f, uint32_t x, uint32_t y, char c, uint32_t color);