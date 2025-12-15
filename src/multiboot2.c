#include "kfs.h"

static int tag_parser(struct kfs *kfs, struct multiboot_tag *tag)
{
	while (tag->type != MULTIBOOT_TAG_TYPE_END) {
		switch (tag->type) {
        		case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
        		{
				kfs->tag_fb = (struct multiboot_tag_framebuffer *) tag;
				break;
        		}

			default:
				break;
        	}
		tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7));
	}
	tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7));

	// framebuffer RGB not found
	if (kfs->tag_fb == NULL)
		return 1;

	return 0;
}

int multiboot2_info_parser(struct kfs *kfs, unsigned long magic, uint32_t multiboot_info_addr)
{
	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
	{
		// Invalid magic number
		return 1;
	}
	
	if (multiboot_info_addr & 7) {
		// Unaligned error
		return 1;
	}

	return tag_parser(kfs, (struct multiboot_tag *) multiboot_info_addr + 8);
}



      