#include <string.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>       // nanosleep()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "common.h"

//definizione shared memory
struct shared_memory *myshm_ptr;
int fd_shm;


void openMemory() {
     /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - richiedere al kernel l'accesso alla memoria condivisa creata da elaborator.c
     * - Gestire gli errori.
     *
     */    
    fd_shm=shm_open(SH_MEM_NAME,O_RDWR,0666);
    if(fd_shm==-1) handle_error("errore open");

    myshm_ptr=mmap(0,sizeof(struct shared_memory),PROT_READ|PROT_WRITE,MAP_SHARED,fd_shm,0);
    if(myshm_ptr==MAP_FAILED) handle_error("errore mmap");


}

void request(){
    int balance = generateRandomNumber(10000);
    while(1){
        /** 
         * COMPLETARE QUI
         *
         * Il producer genera una serie di input da scrivere nel buffer 
         * Ogni input dovraà essere elaborato dall'elaborator
         * a cui viene corrisposto un pagamento (reward)
         * Quando il pagamento supera la disponibilità il producer termina la
         * propria attività
         * 
         * Obiettivi:
         * - gestire la sezione critica opportunamente tramite i semafori
         * - gestire gli errori 
         */

        // sem_t sem_filled=myshm_ptr->sem_filled;
        // sem_t sem_empty=myshm_ptr->sem_empty;
        // sem_t sem_mem=myshm_ptr->sem_mem;

        int reward = generateRandomNumber(1000);
        //printf("BALANCE IS %d\n",balance );
        if (reward>balance){
            printf("not enough money, exit\n");fflush(stdout);
            break;
        }
        balance -= reward;

        int input = generateRandomNumber(100);
        printf("Generated input %d\n",input);
        struct timespec pause = {0};
        pause.tv_nsec = 500000000; // 0.5 s (1*10^9 ns)
        nanosleep(&pause, NULL);
        if(sem_wait(&myshm_ptr->sem_filled)) handle_error("errore semfilled");
        sem_wait(&myshm_ptr->sem_mem);
        myshm_ptr->buf[myshm_ptr->write_index].reward = reward;
        myshm_ptr->buf[myshm_ptr->write_index].input = input;
        myshm_ptr->write_index++;
        if (myshm_ptr->write_index == BUFFER_SIZE)
            myshm_ptr->write_index = 0;
        sem_post(&myshm_ptr->sem_mem);
        sem_post(&myshm_ptr->sem_empty);
    }

}

void closeSemaphores() {
    /** 
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - gestire la chiusura dei semafori
     * - gestire gli errori 
     */
    if(sem_destroy(&myshm_ptr->sem_filled)) handle_error("errore sem_destroy");
    if(sem_destroy(&myshm_ptr->sem_mem)) handle_error("errore sem_destroy");
    if(sem_destroy(&myshm_ptr->sem_empty)) handle_error("errore sem_destroy");
}

void closeMemory() {
    /** 
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - chiudere la memoria condivisa
     * - chiedere al kernel di eliminare la memoria condivisa
     * - gestire gli errori 
     */
    close(fd_shm);
    if(munmap(myshm_ptr,sizeof(struct shared_memory)));


}


int main(int argc, char** argv) {
    initRandomGenerator();

    //load memory
    printf("opening shared memory\n");fflush(stdout);
    openMemory();

    //request cycle
    request();

    //close semaphores
    closeSemaphores();

    //close memory
    closeMemory();

    exit(EXIT_SUCCESS);
}

