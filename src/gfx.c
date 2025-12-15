#include "kfs.h"
#include "gfx.h"
#include "multiboot2.h"

void putpixel(struct kfs *kfs, uint32_t x, uint32_t y, uint32_t color)
{
	struct multiboot_tag_framebuffer *fb = kfs->tag_fb;

	if (x >= fb->common.framebuffer_width || y >= fb->common.framebuffer_height)
		return;

	uint32_t* pixel = (uint32_t*) ((uint8_t*) (uintptr_t) fb->common.framebuffer_addr + fb->common.framebuffer_pitch * y + x * 4);
	*pixel = color;
}

void draw_psf1_glyph(struct kfs *kfs, struct font *f, uint32_t x, uint32_t y, uint16_t glyph_index, uint32_t color)
{
    uint8_t* glyph = (uint8_t*) &f->glyphs[f->header->characterSize * glyph_index];
    uint32_t width = 8;
    uint32_t height = f->header->characterSize;

    for (uint32_t row = 0; row < height; row++) {
        uint8_t bits = glyph[row];

        for (uint32_t col = 0; col < width; col++) {
            if (bits & (0x80 >> col)) {
                putpixel(kfs, x + col, y + row, color);
            }
        }
    }
}

uint32_t glyph_index_for_char(uint8_t c, PSF1_Header* h) {
    if (h->fontMode & 1)
        return (uint16_t)c;  // 512 glyph mode → PSF1 extended
    else
        return c & 0x7F;     // 256 glyphs
}

void fb_putchar(struct kfs *kfs, struct font *f, uint32_t x, uint32_t y, char c, uint32_t color)
{
    uint16_t glyph = glyph_index_for_char((uint8_t)c, f->header);
    draw_psf1_glyph(kfs, f, x, y, glyph, color);
}