#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void reverseTextFile(const char * input_file, const char * output_file){
    
    FILE* f1 = fopen(input_file, "r");
    
    char* line = malloc(1000);
    fseek(f1,0,SEEK_END);
    int cnt = ftell(f1);
    fseek(f1,0,SEEK_SET);
    printf("\n%d\n", cnt);

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

int main(){

    reverseTextFile("p7_input.txt", "p7_output.txt");


    return 0;
}