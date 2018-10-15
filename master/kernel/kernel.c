#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../constants/constants.h"

void exit(int errorCode);

void main(void) {
    // Test clear screen
    cursorLocation cursorLoc_1 = create_cursor_location_with_row_and_col(24, 79);
    print_char('X', kfontColorWhiteOnBlack, get_cursor_offset_from_cursor_location(&cursorLoc_1));

    clear_screen();

    // Test kprint_at without location
    char *helloString = "Hello world! --- from Kernel";
    kprint_at(helloString, kfontColorWhiteOnBlack, NULL, 1);
    
    // Test kprint_at with location
    cursorLocation cursorLoc_2 = create_cursor_location_with_row_and_col(2, 0);
    kprint_at(helloString, NULL, &cursorLoc_2, 0);

    // Test kprint_at with next_line sign.
    char *helloStringWithReturn = "Hello world!\n --- from Kernel, too";
    cursorLocation cursorLoc_3 = create_cursor_location_with_row_and_col(4, 77);
    kprint_at(helloStringWithReturn, NULL, &cursorLoc_3, 1);

    // Test kprint
    kprint(helloStringWithReturn, NULL);


    return;
}

void exit(int errorCode) {
    // TODO: Print the error information and exit;
}