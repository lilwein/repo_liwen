#include "e2A.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseTextFile(const char * input_file, const char * output_file){
    
    FILE* f1 = fopen(input_file, "r");
    int cnt = 0;
    char* line = malloc(1000);
    line = fgets(line, 1000, f1);
    while(line!=NULL) {
        // printf("%s", line);
        cnt++;
        line = fgets(line, 1000, f1);
    }
    fclose(f1);
    // printf("\ncnt: %d\n\n", cnt);

    char **righe = malloc(cnt*sizeof(char*));

    f1 = fopen(input_file, "r");

    for(int i=0; i<cnt; i++) {
        char* line2 = malloc(1000);
        line2 = fgets(line2, 1000, f1);
        righe[i] = line2;
        // printf("%s%s", line2, righe[i]);
    }

    fclose(f1);

    // printf("\n\nrighe:\n");
    // for(int i=0; i<cnt; i++){
    //     printf("%s", righe[i]);
    // }

    FILE* f2 = fopen(output_file, "w+");
    for(int i=cnt-1; i>=0; i--) {
        fputs(righe[i], f2);
    }

    fclose(f2);
}