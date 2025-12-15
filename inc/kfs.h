#pragma once

#include <stddef.h>
#include <stdint.h>

#define VGA_ADDR 0xB8000


struct kfs {	
	struct multiboot_tag_framebuffer *tag_fb;
	// void *fb = (void *) (unsigned long) tag_fb->common.framebuffer_addr;
};
