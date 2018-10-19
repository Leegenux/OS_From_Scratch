#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../constants/constants.h"

void exit(int errorCode);

void main(void) {
    // Test scroll down
    clear_screen();

    int i, j;
    for (i = 1; i <= 79; i++) {
        for (j = 0; j < i; j++) {
            kprint("X", NULL);
        }
        kprint("\n", NULL);
    }
    
    return;
}

void exit(int errorCode) {
    // TODO: Print the error information and exit;
}