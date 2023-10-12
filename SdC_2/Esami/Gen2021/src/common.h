#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

// macros for handling errors
#define handle_error_en(en, msg)    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error(msg)           do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* Configuration parameters */
// macros for producer.c and consumer.c
#define BUFFER_SIZE         10
#define PRNG_SEED           0

#define SH_MEM_NAME         "/mymem"

// definizione cella del buffer
struct cell{
    int reward;
    int input;
};

// definizione struttura dati per la memoria
struct shared_memory {
     /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - definire i semafori unnamed necessari per gestire la concorrenza
     */
    sem_t sem_filled;
    sem_t sem_empty;
    sem_t sem_mem;
    struct cell buf [BUFFER_SIZE];
    int read_index;
    int write_index;
};

// methods defined in common.c
void initRandomGenerator();
int generateRandomNumber(int max);

#endif
