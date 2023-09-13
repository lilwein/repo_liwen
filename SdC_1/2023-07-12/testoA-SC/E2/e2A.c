#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int vowelcount(const char** s, int n){
    if(n==0 || s==NULL) return -1;

    pid_t pid;
    int status;
    int ris = 0;

    for(int i=0; i<n; i++){
        pid_t pid = fork();
        if(pid==0){
            int cnt=0;
            for(int k=0; k<strlen(s[i]); k++){
                char r = s[i][k];
                if(r=='a'||r=='A'||r=='e'||r=='E'||r=='i'||r=='I'||r=='o'||r=='O'||r=='u'||r=='U'){
                    cnt++;
                }
            }
            exit(cnt);
        }
    }


    for(int k=0; k<n; k++){
        if(wait(&status)){
            if(WIFEXITED(status)){
                ris+= WEXITSTATUS(status);
            }
        }
    }
    return ris;
    
}