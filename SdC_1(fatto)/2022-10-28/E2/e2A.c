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

    fseek(file, 0, SEEK_SET);

    char* line = (char*) malloc(1000);
    
    int i = 0, cnt = 0;
    while(fgets(line, 1000, file)){
        if(isalpha(*line)){
            array[i] = line;
            cnt++;
        }
        i++;
    }
    
    fclose(file);

    *list = array;

    return cnt;


}
