// Scrivi la soluzione qui...
void drop_spaces(char* text){
	char *s = text;
	while(*text){
		if(*text == ' ')
			text++;
		else{
			*s = *text;
			s++;
			text++;
		}
	}
	*s = '\0';
	return;
}
