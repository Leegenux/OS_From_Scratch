#include "screen.h"
#include "ports.h"
#include "../constants/constants.h"

/**
 * Following are getting offset functions, mind that the position is what we call the memory offset.
 * each of the index starts from 1.
 * Remember that each and every character is consistent of two bytes. Lower for the character and Higher for the color
 */
unsigned short get_current_cursor_offset(void) {
    /**
     * This function gets current cursor offset from the port 
     * Operations interacting with ports needs parameter check
     */
    // Get the position of the current cursor location
    unsigned short cursorQueryPort = kcursorQueryPort;
    unsigned short cursorResultPort = kcursorResultPort;
    port_byte_out(cursorQueryPort, kcursorOffsetHigherBitsFlag); // high byte
    unsigned int position = port_byte_in(cursorResultPort);
    position = position << 8;

    port_byte_out(cursorQueryPort, kcursorOffsetLowerBitsFlag); // low byte
    position += port_byte_in(cursorResultPort);
    
    if (position > kscreenTotal) {          // Error handling
        exit(1);
    }

    return position * 2;
}

unsigned short get_cursor_offset_from_cursor_location(const cursorLocation * const cursorLoc) {
    /**
     * Note: The general priciple is that we shouldn't create the cursorLocation manually, and in this way we can assure that the 
     */
    if (cursorLoc->row > kscreenGridRow || cursorLoc->col > kscreenGridCol) exit(1);

    return 2 * (cursorLoc->row * kscreenGridCol) + (cursorLoc->col);
}

/**
 * Following are getting cursorLocation functions
 * The cursorLocation is the abstract imaginary location of the cursor in the 80 x 25 grid.
 */
cursorLocation get_cursor_location_from_offset(const unsigned short offset) {
    if (offset > kscreenTotalOffset) {
        exit(1);
    }

    cursorLocation cursorLoc;
    cursorLoc.row = offset / kscreenGridCol;
    cursorLoc.col = offset - cursorLoc.row * kscreenGridCol ;
    return cursorLoc;
}

cursorLocation get_current_cursor_location(void) {
    /**
     * Note: the cursor_offset has already checked by the get_current_cursor_offset() function
     * so here we needn't that extra check.
     */
    unsigned int cursor_offset = get_current_cursor_offset();
    return get_cursor_location_from_offset(cursor_offset);
}

/**
 * Set cursorLocation with cursorLocation structure
 */
void set_cursor_location(const cursorLocation * const cursorLoc) {
    unsigned short cursorOffset = get_cursor_offset_from_cursor_location(cursorLoc) / 2;
    // Lower bits 
    port_byte_out(kcursorQueryPort, kcursorOffsetLowerBitsFlag);
    port_byte_out(kcursorResultPort, cursorOffset & 0xff);
    // Higher bits
    port_byte_out(kcursorQueryPort, kcursorOffsetHigherBitsFlag);
    port_byte_out(kcursorResultPort, cursorOffset >> 8);

    return;
}

/**
 * Kernel print functions
 */
void kprint_at();
void kprint();
void clear_screen();




