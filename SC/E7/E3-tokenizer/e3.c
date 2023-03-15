// Scrivi la soluzione qui...
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGHT 50
char **tokenize(const char *str, const char *delim, int *num_tok){

	*num_tok = 0;
	char* buffer = strcpy(buffer, str);	
	char* token = strtok(str, delim);
	while(token != NULL){
		token = strtok(NULL, delim);
    		num_tok += 1;
	}
	char** pussy =  malloc(sizeof(char*)*(*num_tok));
	token = strtok(buffer, ", ");
	pussy[0]= malloc(MAX_LENGHT*sizeof(char));
	strcpy(pussy[0], token);
	int i = 0;
	while(i < (*num_tok)-1){
		printf("%s\n", pussy[i]);
		++i;
		token = strtok(NULL, ", ");
    		pussy[i]= malloc(MAX_LENGHT*sizeof(char));
		strcpy(pussy[i], token);
	}
}
/*int main(){
	char str[] = "Houston, we have a problem";
	int num_tok = 0;
	char* buffer = strcpy(buffer, str);	
	char* token = strtok(str, ", ");
	while(token != NULL){
		token = strtok(NULL, ", ");
    		num_tok += 1;
	}
	char** pussy =  malloc(sizeof(char*)*num_tok);
	token = strtok(buffer, ", ");
	pussy[0]= malloc(MAX_LENGHT*sizeof(char));
	strcpy(pussy[0], token);
	int i = 0;
	while(i < num_tok-1){
		printf("%s\n", pussy[i]);
		++i;
		token = strtok(NULL, ", ");
    		pussy[i]= malloc(MAX_LENGHT*sizeof(char));
		strcpy(pussy[i], token);
	}
	
}*/
