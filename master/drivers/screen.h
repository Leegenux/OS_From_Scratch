typedef struct cursorlocation {
    unsigned char row;
    unsigned char col;
} cursorLocation;
cursorLocation create_cursor_location_with_row_and_col(unsigned char row, unsigned char col); // 

// Get cursor memory offset
unsigned short get_current_cursor_offset(void);
unsigned short get_offset_from_cursor_location(const cursorLocation *cursorLoc);

// Get cursorLocation
cursorLocation create_cursor_location_with_row_and_col(unsigned char row, unsigned char col);
cursorLocation get_cursor_location_from_offset(unsigned short offset);
cursorLocation get_current_cursor_location(void);

// Set cursorLocation
void set_cursor_location(const cursorLocation *cursorLoc);

// Print functions
// void kprint();
unsigned char kprint_at(const char *charStringToPrint, unsigned char colorStyle, const cursorLocation *cursorLoc, char toMoveCursor);
unsigned char kprint(const char *charStringToPrint, unsigned char colorStyle);
unsigned short print_char(unsigned char charToPrint, unsigned char colorStyle, unsigned short offset);
void clear_screen(void);

// 
void scroll_down(void);