#include "e3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **tokenize(const char *str, const char *delim, int *num_tok){
	int cnt = 0;
	int size = strlen(str);
	char* aux = (char*)malloc(size+1);
	strcpy(aux, str);

	char* token = strtok(aux, delim);
	while(token!=NULL) {
		cnt++;
		token = strtok(NULL, delim);
	}
	*num_tok = cnt;

	char** res = (char**)malloc( cnt * sizeof(char*) );
	
	strcpy(aux, str);

	token = strtok(aux, delim);
	for(int i=0; i<cnt || token!=NULL; i++ ) {
		res[i] = (char*) malloc(strlen(token)+1);
		strcpy(res[i], token);
		token = strtok(NULL, delim);
	}
	free(aux);
	return res;

}