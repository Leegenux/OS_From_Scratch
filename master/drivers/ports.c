#include "ports.h"
/**
 * Get the query result in bytes
 */
unsigned char port_byte_in (unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
    return result;
}

/**
 * Query a port with a byte value
 */
void port_byte_out (unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}

/**
 * Get the query result in word
 */

unsigned short port_word_in (unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a"(result) : "d"(port));
    return result;
}

/**
 * Query a port with a word value
 */

void port_word_out (unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a"(data), "d"(port));
}
