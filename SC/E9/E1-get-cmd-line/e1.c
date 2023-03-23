//SCRIVERE LA SOLUZIONE QUI...
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "e1.h"
#define MAX_TOKENS 64
#define MAX_LINE 1024

void get_cmd_line(char* argv[MAX_TOKENS]){
	char pussy[MAX_LINE];
	fgets(pussy, MAX_LINE, stdin);
	char* token = strtok(pussy, " \n\t");
	int num_tok = 0;
	while(num_tok < MAX_TOKENS && token != NULL){
		argv[num_tok] = (char*) malloc(sizeof(char)*MAX_LINE);
		strcpy(argv[num_tok],token);
		token = strtok(NULL, " \n\t");
		num_tok++;
	}
	argv[num_tok] = NULL;
}
