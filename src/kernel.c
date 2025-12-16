#include "console.h"
#include "kfs.h"
#include "gfx.h"
#include "keyboard.h"
#include "multiboot2.h"

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

	const char* msg = "42 ! ";
	char	keypress;
	
	kfs_init(&kfs, magic, multiboot_info_addr);

	console_write(kfs.tag_fb, kfs.main_font, 0xFFFFFFFF, msg);
	console_write_char(kfs.tag_fb, kfs.main_font, 0xFFFFFFFF, 1);
	console_write_char(kfs.tag_fb, kfs.main_font, 0xFFFFFFFF, '\n');

	console_dump_stack(kfs.tag_fb, kfs.main_font, 0xFFFFFFFF, 16);

	while (1) {
		keypress = get_keypress();
		console_write_char(kfs.tag_fb, kfs.main_font, 0xFFFFFFFF, keypress);
	}
}    
