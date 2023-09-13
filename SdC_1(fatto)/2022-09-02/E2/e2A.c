#include "e2A.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getStudents(const char * filename, student * in_list, int min_mark){

    FILE* file = fopen(filename, "w+");
    while(in_list){
        if( in_list->mark>=min_mark && in_list->mark<=31 ){
            fprintf(file, "%s %s - %d\n", in_list->surname, in_list->name, in_list->mark);
            printf("%s %s - %d\n", in_list->surname, in_list->name, in_list->mark);
        }
        in_list = in_list->next;
    }

    fclose(file);

}
