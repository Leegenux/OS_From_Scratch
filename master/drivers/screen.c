#include "screen.h"
#include "ports.h"
#include "../constants/constants.h"

int get_current_cursor_offset(void) {
    // Get the position of the current cursor location
    short cursorQueryPort = kcursorQueryPort;
    short cursorResultPort = kcursorResultPort;
    port_byte_out(cursorQueryPort, kcursorOffsetHigherBitsFlag); // high byte
    int position = port_byte_in(cursorResultPort);
    position = position << 8;

    port_byte_out(cursorQueryPort, kcursorOffsetLowerBitsFlag); // low byte
    position += port_byte_in(cursorResultPort);

    int offset_from_vga = position * 2;
    // Return the result
    return offset_from_vga;
}