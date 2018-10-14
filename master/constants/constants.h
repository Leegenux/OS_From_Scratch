#define VIDEO_MEMORY (0xb8000)

// cursor related
const extern short kcursorQueryPort;
const extern short kcursorResultPort;
const extern char kcursorOffsetLowerBitsFlag;
const extern char kcursorOffsetHigherBitsFlag;

const unsigned char kscreenGridCol;
const unsigned char kscreenGridRow;
const unsigned short kscreenTotal;
const unsigned short kscreenTotalOffset;

const extern char kfontColorWhiteOnBlack; // color