void interleave(const char* a, const char* b, char* c) {
    do {
        if (*a) *c++ = *a++;
        if (*b) *c++ = *b++;
    } while (*a || *b);
    *c = '\0';
}
