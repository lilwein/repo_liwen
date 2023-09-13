char *my_strcpy(char *dest, const char *src){
    char * aux = dest;
    while (*src){
        *dest = *src;
        src ++;
        dest ++;
    }
    *dest = '\0';
    return aux;
}