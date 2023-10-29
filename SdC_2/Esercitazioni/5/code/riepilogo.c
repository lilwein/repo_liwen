#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

// macros for error handling
#include "common.h"

#define N 100   // child process count
#define M 10    // thread per child process count
#define T 3     // time to sleep for main process

#define FILENAME	"accesses.log"

/*
 * data structure required by threads
 */
typedef struct thread_args_s {
    unsigned int child_id;
    unsigned int thread_id;
} thread_args_t;

/*
 * parameters can be set also via command-line arguments
 */
int n = N, m = M, t = T;

/* TODO: declare as many semaphores as needed to implement
 * the intended semantics, and choose unique identifiers for
 * them (e.g., "/mysem_critical_section") */

#define MAIN_WAITS_FOR_CHILDREN_SEMAPHORE_NAME	"/main_waits_for_children"
#define CHILDREN_WAIT_FOR_MAIN_SEMAPHORE_NAME	"/children_wait_for_main"
#define FILE_CRITICAL_SECTION		"/file_critical_section"

/* TODO: declare a shared memory and the data type to be placed 
 * in the shared memory, and choose a unique identifier for
 * the memory (e.g., "/myshm") 
 * Declare any global variable (file descriptor, memory 
 * pointers, etc.) needed for its management
 */

#define SHM_NAME "/shmem-notification"
#define SHM_SIZE sizeof(int)
int shm_fd;
int* data;

int fd;
sem_t *main_w_child, *child_w_main, *child_termination, *terminate_critical_section, *file_critical_section;

/*
 * Create a named semaphore with a given name, mode and initial value.
 * Also, tries to remove any pre-existing semaphore with the same name.
 */
sem_t *create_named_semaphore(const char *name, mode_t mode, unsigned int value) {
    printf("[Main] Creating named semaphore %s...", name);
	fflush(stdout);
    /* if exist we first unlink it */
    sem_unlink(name);
    sem_t *sem = sem_open(name, O_CREAT|O_EXCL, mode, value);
    if (sem == SEM_FAILED) {
        handle_error("Error creating named semaphore");
    }
    printf("done!!!\n");
    return sem;
}

/*
 * Ensures that an empty file with given name exists.
 */
void init_file(const char *filename) {
    printf("[Main] Initializing file %s...", FILENAME);
    fflush(stdout);
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd<0) handle_error("error while initializing file");
    close(fd);
    printf("closed...file correctly initialized!!!\n");
}


void parseOutput() {
    // identify the child that accessed the file most times
    int* access_stats = calloc(n, sizeof(int)); // initialized with zeros
    printf("[Main] Opening file %s in read-only mode...", FILENAME);
	fflush(stdout);
    int fd = open(FILENAME, O_RDONLY);
    if (fd < 0) handle_error("error while opening output file");
    printf("ok, reading it and updating access stats...");
	fflush(stdout);

    size_t read_bytes;
    int index;
    do {
        read_bytes = read(fd, &index, sizeof(int));
        if (read_bytes > 0)
            access_stats[index]++;
    } while(read_bytes > 0);
    printf("ok, closing it...");
	fflush(stdout);

    close(fd);
    printf("closed!!!\n");

    int max_child_id = -1, max_accesses = -1;
    for (int i = 0; i < n; i++) {
        printf("[Main] Child %d accessed file %s %d times\n", i, FILENAME, access_stats[i]);
        if (access_stats[i] > max_accesses) {
            max_accesses = access_stats[i];
            max_child_id = i;
        }
    }
    printf("[Main] ===> The process that accessed the file most often is %d (%d accesses)\n", max_child_id, max_accesses);
    free(access_stats);
}

void* thread_function(void* x) {
    thread_args_t *args = (thread_args_t*)x;

    /* TODO: protect the critical section using semaphore(s) as needed */

    sem_wait(file_critical_section);

    // open file, write child identity and close file
    int fd = open(FILENAME, O_WRONLY | O_APPEND);
    if (fd < 0) handle_error("error while opening file");
    printf("[Child#%d-Thread#%d] File %s opened in append mode!!!\n", args->child_id, args->thread_id, FILENAME);	

    write(fd, &(args->child_id), sizeof(int));
    printf("[Child#%d-Thread#%d] %d appended to file %s opened in append mode!!!\n", args->child_id, args->thread_id, args->child_id, FILENAME);	

    close(fd);
    printf("[Child#%d-Thread#%d] File %s closed!!!\n", args->child_id, args->thread_id, FILENAME);

    sem_post(file_critical_section);

    free(x);
    pthread_exit(NULL);
}

void mainProcess() {
    /* TODO: the main process waits for all the children to start,
     * it notifies them to start their activities, and sleeps
     * for some time t. Once it wakes up, it notifies the children
     * to end their activities, and waits for their termination.
     * Finally, it calls the parseOutput() method and releases
     * any shared resources. */

    int ret;
    *data = 0;

    for(int i=0; i<n; i++) {
        sem_wait(main_w_child);
    }
    for(int i=0; i<n; i++){
        sem_post(child_w_main);
    }
    sleep(t);

    *data = 1;
    
    int child_status;
    for(int i=0; i<n; i++){
        if ( (ret=wait(&child_status)) == -1) handle_error("main: error on wait()");
        if(WEXITSTATUS(child_status)) handle_error_en(WEXITSTATUS(child_status), "main: child crashed"); 
    }

    parseOutput();

    if( munmap(data, SHM_SIZE) == -1 ) handle_error("main: error on munmap()");
    if( close(shm_fd) == -1 ) handle_error("main: error on close()");
    if( shm_unlink(SHM_NAME) == -1 ) handle_error("main: error on shm_unlink()");

    if( sem_close(main_w_child) == -1 ) handle_error("main: error on sem_close(main_w_child)");
    if( sem_unlink(MAIN_WAITS_FOR_CHILDREN_SEMAPHORE_NAME) == -1 ) handle_error("main: error on sem_unlink()");
    if( sem_close(child_w_main) == -1 ) handle_error("main: error on sem_close(child_w_main)");
    if( sem_unlink(CHILDREN_WAIT_FOR_MAIN_SEMAPHORE_NAME) == -1 ) handle_error("main: error on sem_unlink()");
    
    
    if( sem_close(file_critical_section) == -1 ) handle_error("main: error on sem_close(file_critical_section)");
    if( sem_unlink(FILE_CRITICAL_SECTION) == -1 ) handle_error("main: error on sem_unlink()");

    exit(EXIT_SUCCESS);

}

void childProcess(int child_id) {
    /* TODO: each child process notifies the main process that it
     * is ready, then waits to be notified from the main in order
     * to start. As long as the main process does not notify a
     * termination event [hint: use sem_getvalue() here], the child
     * process repeatedly creates m threads that execute function
     * thread_function() and waits for their completion. When a
     * notification has arrived, the child process notifies the main
     * process that it is about to terminate, and releases any
     * shared resources before exiting. */
    
    int ret;
    

    sem_post(main_w_child);
    sem_wait(child_w_main);

    unsigned int thread_id = 0;
    pthread_t* threads = malloc(m*sizeof(pthread_t));

    do {
        int i;
        memset(threads, 0, m * sizeof(pthread_t));

        for(i=0; i<m; i++){
            thread_args_t *args = (thread_args_t*) malloc(sizeof(thread_args_t));
            args->child_id = child_id;
            args->thread_id = thread_id++;

            ret = pthread_create(&threads[i], NULL, thread_function, args);
            if(ret) handle_error_en(ret, "childProcess: error on pthread_create()");
        }

        for(i=0; i<m; i++){
            ret = pthread_join(threads[i], NULL);
            if(ret) handle_error_en(ret, "childProcess: error on pthread_join()");
        }

        if (*data) break;

    } while(1);

    free(threads);

    if( munmap(data, SHM_SIZE) == -1 ) handle_error("child: error on munmap()");
    if( close(shm_fd) == -1 ) handle_error("child: error on close()");

    if( sem_close(main_w_child) == -1 ) handle_error("child: error on sem_close(main_w_child)");
    if( sem_close(child_w_main) == -1 ) handle_error("child: error on sem_close(child_w_main)");
    if( sem_close(file_critical_section) == -1 ) handle_error("child: error on sem_close(file_critical_section)");

    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    // arguments
    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) m = atoi(argv[2]);
    if (argc > 3) t = atoi(argv[3]);

    // initialize the file
    init_file(FILENAME);

    /* TODO: initialize any semaphore needed in the implementation, and
     * create N children where the i-th child calls childProcess(i); 
     * initialize the shared memory (create it, set its size and map it in the 
     * memory), then the main process executes function mainProcess() once 
     * all the children have been created */


    shm_unlink(SHM_NAME);

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if(shm_fd<0) handle_error("main: error on shm_open()");

    if( ftruncate(shm_fd, SHM_SIZE) == -1 ) handle_error("main: error on ftruncate()");

    data = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(data == MAP_FAILED) handle_error("main: error on mmap()");


    sem_unlink(MAIN_WAITS_FOR_CHILDREN_SEMAPHORE_NAME);
    sem_unlink(CHILDREN_WAIT_FOR_MAIN_SEMAPHORE_NAME);
    sem_unlink(FILE_CRITICAL_SECTION);
    
    main_w_child = sem_open(MAIN_WAITS_FOR_CHILDREN_SEMAPHORE_NAME, O_CREAT | O_EXCL, 0600, 0);
    if(main_w_child == SEM_FAILED) handle_error("main: error on sem_open(MAIN_WAITS_FOR_CHILDREN_SEMAPHORE_NAME)");

    child_w_main = sem_open(CHILDREN_WAIT_FOR_MAIN_SEMAPHORE_NAME, O_CREAT | O_EXCL, 0600, 0);
    if(child_w_main == SEM_FAILED) handle_error("main: error on sem_open(CHILDREN_WAIT_FOR_MAIN_SEMAPHORE_NAME)");

    file_critical_section = sem_open(FILE_CRITICAL_SECTION, O_CREAT | O_EXCL, 0600, 1);
    if(file_critical_section == SEM_FAILED) handle_error("main: error on sem_open(FILE_CRITICAL_SECTION)");



    for(int i=0; i<n; i++){
        pid_t pid = fork();
        if (pid == -1) {
            handle_error("main: error on fork()");
        }
        else if(pid == 0) {
            childProcess(i);
            exit(EXIT_SUCCESS);
        }
    }

    mainProcess();

    exit(EXIT_SUCCESS);
}