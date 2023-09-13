#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define N 5

int main(){
    
    int buffer[N] = {7, 12, 5, 8, 23};
    int* buffer2 = malloc(N*sizeof(int));

    FILE* f = fopen("p6.txt", "r+");
    assert(f!=NULL);

    int num = fwrite(buffer, sizeof(int), N, f);

    int num2 = fread(buffer2, sizeof(int), N, f);

    fclose(f);

    printf("interi scritti: %d\n", num);
    printf("buffer2: ");
    for(int i=0; i<num2; i++) printf("%d ", buffer2[i]);

    return 0;
}