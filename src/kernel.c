#include "kfs.h"

void kernel_main(void) {
	char* vidmem = (char*) VGA_ADDR;
	const char* msg = "Hello World in C";

	for (int i = 0; msg[i] != '\0'; ++i) {
		vidmem[i * 2] = msg[i];
	}
	get_key();
	// while (1) { }
}
