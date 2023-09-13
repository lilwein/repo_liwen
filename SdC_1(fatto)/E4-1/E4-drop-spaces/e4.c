void drop_spaces(char* text){
	char* res = text;
	while(*text){
		if(*text!=' ') {
			*res = *text;
			res++;
		}
		text++;
	}
	*res='\0';
}