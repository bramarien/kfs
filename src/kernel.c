#include "kfs.h"
#include "keyboard.h"

void kernel_main(void) {
	char* vidmem = (char*) VGA_ADDR;
	const char* msg = "Hello World in C";
	char	keypress;
	int	i;

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
