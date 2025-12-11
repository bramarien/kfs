#include "kfs.h"
#include "keyboard.h"

void kernel_main(void) {
	char* vidmem = (char*) VGA_ADDR;
	const char* msg = "Hello World in C";
	int	i;

	i = 0;
	while (msg[i] != '\0') {
		vidmem[i * 2] = msg[i];
		i++;
	}
	while (1) {
		vidmem[i * 2] = get_keystroke();
		i++;
	}
}
