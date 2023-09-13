// scrivere la soluzione qui...
char *my_strcpy(char *dest, const char *src){
	char* ret = dest;
	while (*src){
		*dest = *src;
		src++;
		dest++;
	}
	*dest='\0';
	return ret;
}