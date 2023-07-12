#include "e2A.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 58

void decodeTextFile(const char * encoded_file, const char * key, char ** decoded_text){
    
    FILE* f_key = fopen(key, "r");
    char* keymap = malloc(N);
    char k = fgetc(f_key);
    for(int i=0; i<N;i++){
        keymap[i] = k;
        k = fgetc(f_key);
    }
    fclose(f_key);


    FILE* file = fopen(encoded_file, "r");

    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* res = malloc(len);
    
    char s = fgetc(file);
    int i = 0;
    while(i<len){  
        if( s<=65 || s>= 122 ){
            res[i] = s;
        }
        else{
            res[i] = keymap[s-65];
        }
        s = fgetc(file);
        i++;
    }
    res[i] = '\0';

    *decoded_text = res;
    printf("\nrisultato:\t%s\n", res);

    fclose(file);
}

