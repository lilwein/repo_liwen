#include "e2A.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int vowelcount(const char** s, int n){
    if( s==NULL || n==0) return -1;
    // char** aux = s;

    int i=0;
    int p;
    int res;
    int cnt = 0;

    for(; i<n; i++){
        p = fork();
        if(p==0){  //figlio
            break;
        }
        else{
            wait(&res);
            cnt += res;
        }
        // aux++;
    }

    int c=0;
    if(p==0){
        char* str = s[i];
        while(*str){
            if(*str=='a'||*str=='A'||*str=='e'||*str=='E'||*str=='i'||*str=='I'||*str=='o'||*str=='O'||*str=='u'||*str=='U')
            c++;
        }
        exit(c);
    }
    return cnt;

}