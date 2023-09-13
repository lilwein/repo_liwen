#include <stdio.h>
#include <string.h>

int main(){
    char str[] = "helloo, world!";
    char* token = strtok(str, " ,!");
    while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, " ,!");
    }
    printf("\n%s\n", str);

    return 0;
}