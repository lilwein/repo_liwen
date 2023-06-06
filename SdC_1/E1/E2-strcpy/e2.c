// scrivere la soluzione qui...
char *my_strcpy(char *dest, const char *src){
	char * aux = dest;
	while(*src){
		*dest = *src;
		*dest++;
		*src++;
	}
	*dest = '\0';
	return aux;
}
