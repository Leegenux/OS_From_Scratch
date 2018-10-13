typedef struct cursorlocation {
    unsigned char row;
    unsigned char col;
} cursorLocation;

unsigned int get_current_cursor_offset(void);