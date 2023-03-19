// Scrivi la soluzione qui...
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGHT 50
char **tokenize(const char *str, const char *delim, int *num_tok){

	*num_tok = 0;

	char* buffer = (char*) malloc(256);
    buffer = strcpy(buffer, str) ;

    char* buffer2 = (char*) malloc(256);
    buffer2 = strcpy(buffer2, str) ;	

	char* token = strtok(buffer, delim);
	
    while(token != NULL){
		token = strtok(NULL, delim);
    	*num_tok += 1;
	}

    char** pussy =  malloc(sizeof(char*)*(*num_tok));
	
    token = strtok(buffer2, delim);
	
    for(int i=0; i< *num_tok; i++){
        pussy[i]= (char*) malloc(MAX_LENGHT);
        strcpy(pussy[i], token);
        //printf("%s\n", pussy[i]);
        token = strtok(NULL, delim);
    }
	return pussy;
}

//#define MAIN_E3_C 1

#ifdef MAIN_E3_C
int main(void){
	int c;

    const char* str = "Houston, we have a problem";
    const char* delim = ", ";
	
	char** array = tokenize(str,delim,&c);

	for (int i=0; i<c ; i++){
		printf("%s\n", array[i]);
	}
	return 1;
}
#endif