void dummy_test_entrypoint() {
}

void main() {
    char *video_memory = (char *)0xb8000;
    int i = 0;
    // "Hello world!"
    const char *helloString = "Hello world!";
    for (; i<12; i++) {
        *(video_memory+i) = helloString[i];
    }
}