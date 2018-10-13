#define VIDEO_MEMORY (0xb8000)

// cursor related
extern short kcursorQueryPort;
extern short kcursorResultPort;
extern char kcursorOffsetLowerBitsFlag;
extern char kcursorOffsetHigherBitsFlag;

unsigned char kscreenGridCol;
unsigned char kscreenGridRow;

extern char kfontColorWhiteOnBlack; // color