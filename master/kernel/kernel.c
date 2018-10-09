#include "../drivers/ports.h"

void dummy_test_entrypoint() {
}

void main(void) {
    // Get the video_memory
    char *video_memory = (char *)0xb8000;

    // // Print the hello world string
    // int i = 0;
    // const char *helloString = "Hello world!                            ";
    // for (; i<16; i++) {
    //     video_memory[2*i] = helloString[i];
    //     video_memory[2*i + 1] = 0x0f;
    // }

    // Get the position of the current cursor location
    short cursorPort = 0x3d4;
    port_byte_out(cursorPort, 14); // high byte
    int position = port_byte_in(cursorPort);
    position = position << 8;

    port_byte_out(cursorPort, 15); // low byte
    position += port_byte_in(cursorPort);

    int offset_from_vga = position * 2;
    // Print the Variable offset_from_vga
    char reverseNumber[20];
    char index;
    for (index = 0; offset_from_vga > 0; offset_from_vga /= 10, index++) {
        reverseNumber[index] = '0' + offset_from_vga - offset_from_vga / 10 * 10;
    }

    char printIndex;
    for (printIndex = 0; index >= 0; index--, printIndex++) {
        video_memory[printIndex * 2] = reverseNumber[index];
        video_memory[printIndex * 2 + 1] = 0x0f;
    }


    // Print the "Z"
    // video_memory[offset_from_vga] = 'X';
    // video_memory[offset_from_vga + 1] = 0x0f;
    // for (int i = 0; i < 16; i++) {
    //     video_memory[offset_from_vga + 2*i] = 'X';
    //     video_memory[offset_from_vga + 2*i + 1] = 0x0f;
    // }
}