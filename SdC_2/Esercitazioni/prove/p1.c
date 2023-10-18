#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 4

void* hello(void* arg){
    printf("%s\n", (char*)arg);
}

int main(int argc, char const *argv[]){
    
    pthread_t tid[NUM_THREADS];
    for(int i=0; i<NUM_THREADS; i++){
        char n[16];
        sprintf(n, "%d", i);
        // char* str = malloc(32);
        char str[] = "Thread ";
        strcat(str, n);
        printf("#\t%s\n", str);
        pthread_create(&tid[i], NULL, hello, str);
    }
    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(tid[i], NULL);
    }

    return 0;
}
