#include "kfs.h"
#include "gfx.h"
#include "keyboard.h"
#include "multiboot2.h"

static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;

void fb_write(struct kfs *kfs, struct font *f, const char *s)
{
	uint32_t char_w = 8;
	uint32_t char_h = f->header->characterSize;

	while (*s) {
		if (*s == '\n') {
			cursor_x = 0;
			cursor_y += char_h;
		} else {
			fb_putchar(kfs, f, cursor_x, cursor_y, *s, 0xFFFFFFFF);
			cursor_x += char_w;

			if (cursor_x + char_w >= kfs->tag_fb->common.framebuffer_width) {
				cursor_x = 0;
				cursor_y += char_h;
			}
		}
		s++;
	}
}

void fb_write_char(struct kfs *kfs, struct font *f, char c)
{
    char s[2];   // 1 for char, 1 for '\0'
    s[0] = c;
    s[1] = '\0';

    fb_write(kfs, f, s);
}


static int main_font_init(struct kfs *kfs) 
{
	kfs->main_font->header = (PSF1_Header *)_binary_fonts_unifont_apl8x16_psf_start;
	kfs->main_font->glyphs = _binary_fonts_unifont_apl8x16_psf_start + sizeof(PSF1_Header);

	if (kfs->main_font->header->magic != PSF1_FONT_MAGIC)
		return 1;

	return 0;
}

static int kfs_init(struct kfs *kfs, unsigned long magic, uint32_t multiboot_info_addr) 
{
	int error = 0;

	kfs->tag_fb = NULL;
	
	error = multiboot2_info_parser(kfs, magic, multiboot_info_addr);
	if (error)
		return 1;

	error = main_font_init(kfs);
	if (error)
		return 1;

	return 0;
}

void kernel_main(unsigned long magic, uint32_t multiboot_info_addr) 
{
	struct kfs kfs;

	const char* msg = "Welcome Sir ! ";
	char	keypress;
	
	kfs_init(&kfs, magic, multiboot_info_addr);

	fb_write(&kfs, kfs.main_font, msg);
	fb_write_char(&kfs, kfs.main_font, 1);

	while (1) {
		keypress = get_keypress();
		fb_write_char(&kfs, kfs.main_font, keypress);
	}
}    
