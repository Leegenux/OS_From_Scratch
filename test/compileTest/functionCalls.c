int callee(int a, int b, int c) {
    int d = a + b / c;
    return d;
}

int caller(int a, int b, int c) {
    int d = callee(a, b, c);
    return d;
}