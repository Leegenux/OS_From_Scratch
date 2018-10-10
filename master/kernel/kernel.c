#include "../drivers/ports.h"

// void dummy_test_entrypoint() {
// }

void main(void) {
    // Get the video_memory
    char *video_memory = (char *)0xb8000;

    // Get the position of the current cursor location
    short cursorQueryPort = 0x3d4;
    short cursorResultPort = 0x3d5;
    port_byte_out(cursorQueryPort, 14); // high byte
    int position = port_byte_in(cursorResultPort);
    position = position << 8;

    port_byte_out(cursorQueryPort, 15); // low byte
    position += port_byte_in(cursorResultPort);

    int offset_from_vga = position * 2;

    // Print the hello world string at current cursor
    int i = 0;
    const char *helloString = "Hello world!                            ";
    for (; i < 25; i++) {
        video_memory[2*i + offset_from_vga] = helloString[i];
        video_memory[2*i + offset_from_vga + 1] = 0x0f;
    }
}