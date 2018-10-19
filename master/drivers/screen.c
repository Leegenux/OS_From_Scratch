#include "screen.h"
#include "ports.h"
#include "../constants/constants.h"
#include "../kernel/utils.h"

/**
 *  You should always tell them apart(cursorLocation, position and offset) when maintaining the code
 * 1. The port just returns the position and offset = position * 2
 * 2. cursorLocation is the imaginary location of the 80 * 25 grid, based on the position, starting from 0 and 0
 */

/**
 * Following are getting offset functions, mind that the position is what we call the memory offset.
 * each of the index starts from 1.
 * Remember that each and every character is consistent of two bytes. Lower for the character and Higher for the color
 */
unsigned short get_current_cursor_offset(void) { // TESTED
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
    
    if (position >= kscreenTotal) {          // Error handling
        exit(1);
    }

    return position * 2;
}

unsigned short get_cursor_offset_from_cursor_location(const cursorLocation *cursorLoc) { // TESTED
    /**
     * Note: The general priciple is that we shouldn't create the cursorLocation manually, and in this way we can assure that the 
     */
    if (cursorLoc->row >= kscreenGridRow || cursorLoc->col >= kscreenGridCol) exit(1);

    return 2 * ((cursorLoc->row * kscreenGridCol) + (cursorLoc->col));
}

/**
 * Following are getting cursorLocation functions
 * The cursorLocation is the abstract imaginary location of the cursor in the 80 x 25 grid.
 */
cursorLocation create_cursor_location_with_row_and_col(unsigned char row, unsigned char col) {// TESTED
    cursorLocation cursorLoc;
    cursorLoc.row = row;
    cursorLoc.col = col;
    return cursorLoc;
}

cursorLocation get_cursor_location_from_offset(unsigned short offset) {// TESTED
    // Error check
    if (offset > kscreenTotalOffset) {
        exit(1);
    }
    // Return the cursorLoc
    unsigned short position = offset >> 1;
    cursorLocation cursorLoc;
    cursorLoc.row = position / kscreenGridCol;
    cursorLoc.col = position - cursorLoc.row * kscreenGridCol ;
    return cursorLoc;
}

cursorLocation get_current_cursor_location(void) {     // TESTED
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
void set_cursor_location(const cursorLocation *cursorLoc) { // TESTED
    unsigned short cursorPosition = get_cursor_offset_from_cursor_location(cursorLoc) >> 1;
    // Lower bits 
    port_byte_out(kcursorQueryPort, kcursorOffsetLowerBitsFlag);
    port_byte_out(kcursorResultPort, cursorPosition & 0xff);
    // Higher bits
    port_byte_out(kcursorQueryPort, kcursorOffsetHigherBitsFlag);
    port_byte_out(kcursorResultPort, cursorPosition >> 8);
}

/**
 * Kernel print functions
 */
unsigned char kprint_at(const char *charStringToPrint, unsigned char colorStyle, const cursorLocation *cursorLoc, char toMoveCursor) {//TESTED
    /**
     * 
     */
    // default colorStyle and other error handling
    colorStyle = colorStyle ? : kfontColorWhiteOnBlack;
    if (!charStringToPrint) {
        return FAILURE;
    }
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

    // Move the cursor
    if (toMoveCursor) {
        // Move the cursor and possibly scrolls the screen
        cursorLocation tempLoc = get_cursor_location_from_offset(offset); // Position = offset / 2, but here offset is required
        set_cursor_location(&tempLoc);
    }

    return SUCCESS;
}

unsigned char kprint(const char *charStringToPrint, unsigned char colorStyle) {//TESTED
    /**
     * Print at the current location and by the way moves the cursor
     */
    cursorLocation currentCursorLoc = get_current_cursor_location();
    return kprint_at(charStringToPrint, colorStyle, &currentCursorLoc, 1);
}

unsigned short print_char(unsigned char charToPrint, unsigned char colorStyle, unsigned short offset) {//TESTED
    /**
     * It won't automatically sets the current cursor location only when scroll is needed (moves cursor up)
     */
    // Write the character into the Video Memory
    char *videoMemToWrite = (char *)VIDEO_MEMORY + offset;
    cursorLocation nextLocation = get_cursor_location_from_offset(offset + 2);      // Default is to Plus 2

    if (charToPrint != '\n') {  // Handle writing to VGA
        videoMemToWrite[0] = charToPrint;
        videoMemToWrite[1] = colorStyle;
    } else {    // Handle the '\n' character
        nextLocation.row += (nextLocation.col != 0);        // If nextLocation.col == 0, then Plus 2 has already switched the row
        nextLocation.col = 0;
    }
    
    // Scrolls if beyond bound
    if (nextLocation.row >= kscreenGridRow) {
        scroll_down();
        nextLocation.row--;
    }

    return get_cursor_offset_from_cursor_location(&nextLocation);
}

void scroll_down(void) {//TESTED
    // Set the cursorLocation
    cursorLocation currentLoc = get_current_cursor_location();
    currentLoc.row -= (currentLoc.row != 0);   // If the cursor goes beyond the top, then don't move up.

    set_cursor_location(&currentLoc);
    // Copies the characters
    unsigned char index;
    char *videoMem = (char *)VIDEO_MEMORY;
    for (index = 1; index < kscreenGridRow; index++) {
        memory_copy(videoMem + 2 * index * kscreenGridCol,
                    videoMem + 2 * (index-1) * kscreenGridCol,
                    2 * sizeof(char) * kscreenGridCol);
    }
    // Sets last line empty 
    char *lastLineIterator = (char *)VIDEO_MEMORY + (kscreenGridRow - 1) * kscreenGridCol * 2;
    for (; lastLineIterator < (char *)VIDEO_MEMORY_END; lastLineIterator += 2) { 
        lastLineIterator[0] = ' ';
        lastLineIterator[1] = kfontColorWhiteOnBlack;
    }
}

void clear_screen(void) { // TESTED
    /**
     *
     */
    // Set the chars
    char *currentLoc = (char *)VIDEO_MEMORY;
    while (currentLoc <= (char *)VIDEO_MEMORY_END) {
        *(currentLoc++) = (char)0x00;
        *(currentLoc++) = kfontColorWhiteOnBlack;
    }
    // Set the current cursor
    cursorLocation cursorZero;
    cursorZero.col = 0;
    cursorZero.row = 0;
    set_cursor_location(&cursorZero);
}


