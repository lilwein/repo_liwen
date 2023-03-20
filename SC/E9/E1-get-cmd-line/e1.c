//SCRIVERE LA SOLUZIONE QUI...
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "e1.h"
char* cpy(const char* in){
	size_t n = strlen(in);
	char* out = malloc(n+1);
	strcpy(out, in);
	return out;
}
void get_cmd_line(char* argv[MAX_TOKENS]){
	char line[MAX_LINE];
	fgets(line, MAX_LINE, stdin);
	char* token = strtok(line, " \t\n");
	int argc = 0;
	while (argc < MAX_TOKENS && token != NULL){
		argv[argc++] = cpy(token);
		token = strtok(NULL, " \t\n");
	}
	argv[argc] = NULL;
}
