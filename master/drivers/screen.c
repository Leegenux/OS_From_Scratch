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

unsigned short get_cursor_offset_from_cursor_location(const cursorLocation *cursorLoc) {
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
cursorLocation get_cursor_location_from_offset(unsigned short offset) {
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
void set_cursor_location(const cursorLocation *cursorLoc) {
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
void kprint_at(const char *charStringToPrint, unsigned char colorStyle, const cursorLocation *cursorLoc, char toMoveCursor) {
    // Get the offset
    unsigned short offset;
    if (cursorLoc == NULL) {
        offset = get_current_cursor_offset();
    } else {
        offset = get_cursor_offset_from_cursor_location(cursorLoc);
    }

    // Start to print until occurence of 0x00, and by the way manage the offset
    unsigned int index = 0;
    while (charStringToPrint[index] != 0x00) {
        offset = print_char(charStringToPrint[index++], colorStyle, offset);
    }

    return;
}

unsigned short print_char(unsigned char charToPrint, unsigned char colorStyle, unsigned short offset) {
    // Write the character
    char *videoMemToWrite = (char *)VIDEO_MEMORY + offset;
    videoMemToWrite[0] = charToPrint;
    videoMemToWrite[1] = colorStyle;

    // Handle the '\n' character
    if (charToPrint == '\n') {
        cursorLocation tempLocation = get_cursor_location_from_offset(offset);
        tempLocation.col = 0;
        tempLocation.row++;
        offset = get_cursor_offset_from_cursor_location(&tempLocation);
    } else {
        offset += 2;
    }
    return offset;
}

void clear_screen(void) {
    // Set the chars
    char *currentLoc = (char *)VIDEO_MEMORY;
    while (currentLoc <= VIDEO_MEMORY_END) {
        *(currentLoc++) = NULL;
        *(currentLoc++) = kfontColorWhiteOnBlack;
    }
    // Set the current cursor
    cursorLocation cursorZero;
    cursorZero.col = 0;
    cursorZero.row = 0;
    set_cursor_location(&cursorZero);

    return;
}




