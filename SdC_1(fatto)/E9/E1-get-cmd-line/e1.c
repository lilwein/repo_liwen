#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "e1.h"
#define MAX_TOKENS 64
#define MAX_LINE 1024

void get_cmd_line(char* argv[MAX_TOKENS]){
	char line[MAX_LINE];
	fgets(line, MAX_LINE, stdin);

	char* delim = " \n\t";
	char* token = strtok(line, delim);

	int i=0;
	while(token && i<MAX_TOKENS){
		
		argv[i] = (char*)malloc(sizeof(char)*MAX_LINE);
		strcpy(argv[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	argv[i] = NULL;
}
