#include "kfs.h"
#include "keyboard.h"
#include "multiboot2.h"

static int kfs_init(struct kfs *kfs, unsigned long magic, uint32_t multiboot_info_addr) 
{
	int error = 0;

	kfs->tag_fb = NULL;

	error = multiboot2_info_parser(kfs, magic, multiboot_info_addr);
	
	return error;
}


void kernel_main(unsigned long magic, uint32_t multiboot_info_addr) 
{
	struct kfs kfs;

	char* vidmem = (char*) VGA_ADDR;
	const char* msg = "Hello World in C";
	char	keypress;
	int	i;
	
	kfs_init(&kfs, magic, multiboot_info_addr);
	
	i = 0;
	while (msg[i] != '\0') {
		vidmem[i * 2] = msg[i];
		i++;
	}
	while (1) {
		keypress = get_keypress();
		vidmem[i * 2] = keypress;
		i++;
	}
}    
