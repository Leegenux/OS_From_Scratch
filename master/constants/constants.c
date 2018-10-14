 
 // cursor related
const short kcursorQueryPort = 0x3d4;
const short kcursorResultPort = 0x3d5;
const char kcursorOffsetLowerBitsFlag = 15;
const char kcursorOffsetHigherBitsFlag = 14;

const unsigned char kscreenGridCol = 80;
const unsigned char kscreenGridRow = 25;
const unsigned short kscreenTotal = 80 * 25;
const unsigned short kscreenTotalOffset = 80 * 25 * 2; 

const char kfontColorWhiteOnBlack = 0x0f; // color