#include "e2A.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 256

int my_min(int* array, int n){
    int res = array[0];
    for(int i=1; i<n; i++){
        if(res > array[i] ) res = array[i];
    }
    return res;
}

int my_max(int* array, int n){
    int res = array[0];
    for(int i=1; i<n; i++){
        if(res < array[i] ) res = array[i];
    }
    return res;
}

float my_avg(int* array, int n){
    float cnt=0;
    for(int i=0; i<n; i++){
        cnt += array[i];
    }
    return (float) cnt/n;
}

int examStats(const char* fname, int *min, int *max, float *avg){
    
    FILE* file = fopen(fname, "r");
    if(file==NULL) return -1;
    
    char* line = (char*) malloc(N*sizeof(char));

    int* voti = malloc(1000*sizeof(int));
    int i = 0, cnt = 0;
    
    char* c = fgets(line, N, file);

    while(c){
        char* delim = "-";
        char* token = strtok(c, delim);
        token = strtok(NULL, delim);
        token = strtok(NULL, delim);
        
        int voto = atoi(token);
        voti[i] = voto;
        if(voto>=18 && voto <=30) cnt++;

        c = fgets(line, N, file);
        i++;
        
    }
    fclose(file);
    *min = my_min(voti, i);
    *max = my_max(voti, i);
    *avg = my_avg(voti, i);

    return cnt;
}

