#include "screen.h"
#include "ports.h"
#include "../constants/constants.h"
// #include <assert.h>

/**
 * Following are getting offset functions
 * Remember that each and every character is consistent of two bytes. Lower for the character and Higher for the color
 */
unsigned int get_current_cursor_offset(void) {
    // Get the position of the current cursor location
    unsigned short cursorQueryPort = kcursorQueryPort;
    unsigned short cursorResultPort = kcursorResultPort;
    port_byte_out(cursorQueryPort, kcursorOffsetHigherBitsFlag); // high byte
    unsigned int position = port_byte_in(cursorResultPort);
    position = position << 8;

    port_byte_out(cursorQueryPort, kcursorOffsetLowerBitsFlag); // low byte
    position += port_byte_in(cursorResultPort);
    
    // assert(position <= kscreenGridCol * kscreenGridRow);
    unsigned int offset_from_vga = position * 2;


    // Return the result
    return offset_from_vga;
}

unsigned int get_cursor_offset_from_cursor_location(cursorLocation *cursorLoc) {
    return 2 * (cursorLoc->row * kscreenGridCol) + (cursorLoc->col);
}

/**
 * Following are getting cursorLocation functions
 */
cursorLocation get_current_cursor_location(void) {
    unsigned int cursor_offset = get_current_cursor_offset();
    cursorLocation cursorLoc;
    cursorLoc.row = cursor_offset / kscreenGridCol;
    cursorLoc.col = cursor_offset - cursorLoc.row * kscreenGridCol;
    
    return cursorLoc;
}


