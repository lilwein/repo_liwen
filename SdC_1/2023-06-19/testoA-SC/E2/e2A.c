#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    char* line = (char*) malloc(N*sizeof(char));
    char* l = fgets(line, N, file);

    int* lis = (int*) malloc(1000 *sizeof(int));
    int cnt = 0;

    while(l){
        char * tok = strtok(line, "-");
        strtok(NULL, "-");
        tok = strtok(NULL, "-");
        int voto = atoi(tok);
        if(voto>=18){
            lis[cnt]=voto;
            cnt++;
        }
        l = fgets(line, N, file);
    }
    fclose(file);

    *min = my_min(lis, sizeof(lis));
    *max = my_max(lis, sizeof(lis));
    *avg = my_avg(lis, sizeof(lis));

    return cnt;




}