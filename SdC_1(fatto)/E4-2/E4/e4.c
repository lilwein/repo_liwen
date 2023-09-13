static int is_prefix(const char* sub, const char* s) {
    while (*sub == *s && *sub!=0 && *s!=0) {
        sub++;
        s++;
    }
    return *sub == 0;
}

int count_substrings(const char* s, const char* sub) {
    int cnt = 0;
    do cnt += is_prefix(sub,s); while(*s++);
    return cnt;
}