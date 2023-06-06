//SCRIVI LA SOLUZIONE QUI...

#include "e2.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE	1024
#define MAX_TOKENS	64

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

int do_shell(const char* prompt){
	while(1){
		printf("%s", prompt);
		char* argv[MAX_TOKENS];
		get_cmd_line(argv);
		if(strcmp(argv[0], "quit") == 0)
				break;
		else if(argv[0] != NULL){
			int res;
			pid_t pid = fork();
			if(pid == -1){
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if(pid == 0){
				res = execvp(argv[0], argv);
				if(res == -1){
					printf("unknown command %s\n", argv[0]);
					_exit(EXIT_FAILURE);
				}
			}
			pid = wait(NULL);
			if(pid == -1){
				perror("wait");
				exit(EXIT_FAILURE);
			}
		}
	}
	return EXIT_SUCCESS;
}
