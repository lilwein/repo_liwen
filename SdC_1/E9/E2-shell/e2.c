#include "e2.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE	1024
#define MAX_TOKENS	64

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

int do_shell(const char* prompt){
    while(1){
        printf("%s", prompt);
        char* argv[MAX_TOKENS];
		get_cmd_line(argv);
        if(argv[0]==NULL) continue;
        if(!strcmp(argv[0], "quit")) break;
        if(argv[0]!=NULL){
            int pid = fork();
            if(pid == -1){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if(!pid){ //figlio
                int ris = execvp(argv[0], argv);
                if(ris){
                    printf("unknown command %s\n", argv[0]);
                    exit(EXIT_FAILURE);
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
