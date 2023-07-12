#include "e2A.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int loadStringsFromFile (const char * filename, char *** list){


    FILE* file = fopen(filename, "r");

    int rows=0;
    char aux[1000];
    while(fgets(aux, 1000, file)){
        rows++;
    }
    char** array = (char**) malloc(rows*sizeof(char*));
    // printf("\n\nrows:\t%d\n\n", rows);

    fseek(file, 0, SEEK_SET);

    char* line = fgets(line, 1000, file);

    // printf("\n\n%s\n\n", line);
    int i = 0, cnt = 0;
    while(i<rows){
        if(isalpha(*line)){
            array[i] = line;
            cnt++;
        }
        // printf("\n\n%s\n\n", array[i]);
        fgets(line, 1000, file);
        i++;
    }
    
    fclose(file);
    // return 1;

    *list = array;

    return cnt;


}
