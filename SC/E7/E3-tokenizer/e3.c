// Scrivi la soluzione qui...
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGHT 1027
char **tokenize(const char* str, const char* delim, int* num_tok){
	*num_tok = 0;
	char* buffer1 = (char*)malloc(sizeof(char)*MAX_LENGHT);
	strcpy(buffer1, str);	
	char* token = strtok(buffer1, delim);
	while(token != NULL){
		token = strtok(NULL, delim);
    		*num_tok += 1;
	}
	char** pussy =  malloc(sizeof(char*)*(*num_tok));
	char* buffer2 = (char*)malloc(sizeof(char)*MAX_LENGHT);
	strcpy(buffer2, str);
	token = strtok(buffer2, ", ");
	for(int i = 0; i < *num_tok; i++){
		pussy[i]= malloc(MAX_LENGHT*sizeof(char));
		strcpy(pussy[i], token);
		token = strtok(NULL, ", ");
	}
	return pussy;
}
