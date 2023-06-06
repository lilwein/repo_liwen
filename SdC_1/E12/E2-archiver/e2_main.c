#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "e2.h"

int score, trials;

#define TRACE 0
#define FILENAME_LEN 256
#define BUF_SIZE 4096

static void check_error(long res, char* msg) {
    if (res != -1) return;
    perror(msg);
    exit(EXIT_FAILURE);
}

static int check_header(const char* filename, int fd, int fd_archive) {
    char buf[FILENAME_LEN+1];
    off_t archive_file_size, file_size;
    ssize_t res;

    // check filename
    res = read(fd_archive, buf, FILENAME_LEN);
    check_error(res, "open");
    buf[FILENAME_LEN]=0;
    #if TRACE
    printf("%s %s\n", filename, buf);
    #endif
    if (strcmp(filename, buf) != 0) return 0;

    // check file size
    res = read(fd_archive, &archive_file_size, sizeof(archive_file_size));
    check_error(res, "read");
    file_size = lseek(fd, 0, SEEK_END);
    check_error(file_size, "lseek");
    #if TRACE
    printf("%lu %lu\n", file_size, archive_file_size);
    #endif
    if (archive_file_size != file_size) return 0;

    return 1;
}

static int check_file(int fd, int fd_archive) {
    int res, res1, res2;
    char buf1[BUF_SIZE], buf2[BUF_SIZE];
    res = lseek(fd, 0, SEEK_SET);
    check_error(res, "lseek");
    for (;;) {
        res1 = read(fd, buf1, BUF_SIZE);
        check_error(res1, "read");
        if (res1 == 0) break;
        #if TRACE
        printf("\n------------ (fd read %d bytes)\n", res1);
        write(1, buf1, res1);
        #endif
        res2 = read(fd_archive, buf2, res1);
        check_error(res2, "read");
        #if TRACE
        printf("\n------------ (fd_archive read %d bytes)\n", res2);
        write(1, buf2, res2);
        printf("\n------------\n");
        #endif
        if (memcmp(buf1, buf2, res1) != 0) return 0;
    }
    return 1;
}

int check(const char *archive, const char *files[], int n) {
    int fd, fd_archive, res, i, ok = 1;

    fd_archive = open(archive, O_RDONLY);
    check_error(fd_archive, "open");

    // iterate over files
    for (i=0; i<n && ok; ++i) {
        fd = open(files[i], O_RDONLY);
        check_error(fd, "open");

        ok = ok && check_header(files[i], fd, fd_archive);
        ok = ok && check_file(fd, fd_archive);

        res = close(fd);
        check_error(res, "close");
    }

    res = close(fd_archive);
    check_error(res, "close");

    return ok;
}

void test(const char *archive, const char *files[], int n) {
    int ok;
    trials++;
    archiver(archive, files, n);
    ok = check(archive, files, n);
    printf("Test %d: [corretto=%d]\n", trials, ok);
    score += ok;
}

int main() {

    const char* files[] = { "e2.h", "e2.c", "e2_main.c", "Makefile", "e2" };

    test("archive.dat", files, 0);
    test("archive.dat", files+2, 1);
    test("archive.dat", files, 5);

    printf("Risultato: %d/%d\n", score, trials);
    return EXIT_SUCCESS;
}
