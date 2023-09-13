#include "e2A.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

int vowelcount(const char** s, int n){
    if( s==NULL || n==0) return -1;

    pid_t p;
    int status;
    int cnt = 0;
    
    for(int i=0; i<n; i++){
        p = fork();

        // processo figlio
        if(p==0){
            char* str = s[i];
            int len = strlen(str);
            int vocali = 0;

            for(int j=0; j<len; j++){
                char ch = tolower(str[j]);
                if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u') vocali++;
            }

            exit(vocali);
        }
        
    }
    
    for (int i = 0; i < n; i++) {
	    while(wait(&status) > 0){
			if(WIFEXITED(status)){
				cnt += WEXITSTATUS(status);
			}
	    }
    }
    
    
    
    return cnt;

}