char *my_strcat(char *dest, const char *src){
	char * aux = dest;
	while(*dest){
		dest++;
	}
	while(*src){
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return aux;
}