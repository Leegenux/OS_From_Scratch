// Generic
extern const void *NULL;

// OS-specific
/**
 * Instruction: How to reference the constants in assembly code ?
 * 1. Make the constant public using assembly directive : global
 * 2. Import the constant using C extern.
 * 3. Link together
 */
extern char CODE_SEG;
extern char DATA_SEG;

// cursor related
extern const short kcursorQueryPort;
extern const short kcursorResultPort;
extern const char kcursorOffsetLowerBitsFlag;
extern const char kcursorOffsetHigherBitsFlag;

extern const unsigned char kscreenGridCol;
extern const unsigned char kscreenGridRow;
extern const unsigned short kscreenTotal;
extern const unsigned short kscreenTotalOffset;
extern const unsigned int VIDEO_MEMORY;
extern const unsigned int VIDEO_MEMORY_END;

extern const char kfontColorWhiteOnBlack; // color

// Status const
typedef unsigned char typeStatus;
extern const typeStatus SUCCESS;
extern const typeStatus FAILURE;
