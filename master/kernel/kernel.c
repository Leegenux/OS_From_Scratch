#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../constants/constants.h"

void exit(int errorCode);

void main(void) {
    // Get the video_memory
    char *video_memory = (char *)(VIDEO_MEMORY);

    int offset_from_vga = get_current_cursor_offset();

    // Print the hello world string at current cursor
    int i = 0;
    const char *helloString = "Message from kernel: Hello world!                                   ";
    for (; i < 70; i++) {
        video_memory[2*i + offset_from_vga] = helloString[i];
        video_memory[2*i + offset_from_vga + 1] = kfontColorWhiteOnBlack;
    }

    return 0;
}

void exit(int errorCode) {
    // TODO: Print the error information and exit;
}