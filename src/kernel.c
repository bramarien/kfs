#define VGA_ADDR 0xB8000

void kmain(void) {

    char* vidmem = (char*) VGA_ADDR;
    const char* msg = "Hello World in C";

    for (int i = 0; msg[i] != '\0'; ++i) {
        vidmem[i * 2] = msg[i];
    }

    // Halt
    while (1) { }
}