#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char dest[12] = "hello";
    // char* dest = (char*) malloc(12*sizeof(char));
    
    char* ao = strcat(dest, " world");
    printf("ao: %s\tdest: %s\n\n", ao, dest);
    *ao++;
    *ao++;
    printf("ao: %s\tdest: %s\n", ao, dest);
    printf("ao: %p\tdest: %p\n\n\n\n", ao, dest);

    return 0;
}