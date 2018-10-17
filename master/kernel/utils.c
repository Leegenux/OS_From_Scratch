void memory_copy(char *source, char *dest, int nBytes) {
    int index;
    for (index = 0; index < nBytes; index++) {
        dest[index] = source[index];
    }
}

/**
 * 
 */
void int_to_ascii(int sourceNumber, char dest[]) {
    /**
     *  This function convert the int into a inverse string
     *  Reason why inverse: Because the digit's length is not previoursly known.
     *  Inversion makes the function lighter and faster
     */
    int index, sign;

    // Turn minus into positive 
    if ((sign = sourceNumber) < 0) index = -index;

    index = 0;
    do {
        dest[index++] = sourceNumber % 10 + '0';
    } while ((sourceNumber /= 10) > 0);

    if (sign < 0) dest[index++] = '-';
    dest[index] = '\0';
}