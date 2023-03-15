// Scrivere la soluzione qui
int substring(const char* s, const char* sub){
	while(*s){
		if (*s == *sub){
			s++;
			sub++;
		}
		if(!*sub)
			return 1;
	}
	return 0;
}	
	
int count_substrings(const char* s, const char* sub){
	if(!*s && !*sub)
		return 1;
	int count = 0;
	while(*s){
		if(*s == *sub)
			count += substring(s, sub);
		s++;
	}
	return count;
}
