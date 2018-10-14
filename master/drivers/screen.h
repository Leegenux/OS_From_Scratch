typedef struct cursorlocation {
    unsigned char row;
    unsigned char col;
} cursorLocation;

// Get cursor memory offset
unsigned short get_current_cursor_offset(void);
unsigned short get_cursor_offset_from_cursor_location(const cursorLocation * const cursorLoc);

// Get cursorLocation
cursorLocation get_cursor_location_from_offset(const unsigned short offset);
cursorLocation get_current_cursor_location(void);

// Set cursorLocation
void set_cursor_location(const cursorLocation * const cursorLoc);

// Print functions
void kprint();
void kprint_at();
void clear_screen();