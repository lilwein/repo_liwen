#include "e2.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FILEHEADER_LEN 256
#define BUF_SIZE 4096

void check_error(ssize_t res, char* msg){
	if(res !=-1)
		return;
	perror(msg);
	exit(EXIT_FAILURE);	
}

void copy_file(int fd_dest, int fd_src){
	ssize_t res;
	char buf[BUF_SIZE];
	while(1){
		res = read(fd_src, buf, BUF_SIZE);
		check_error(res, "read");
		if(res == 0)
			break;
		res = write(fd_dest, buf, res);
		check_error(res, "write");
	}
}

void archiver(const char* archive, const char** files, int n) {
	char file_pathname[FILEHEADER_LEN];
	int fd_archive = open(archive, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_error(fd_archive, "open");	
	int fd;
	off_t size;
	ssize_t res;
	for(int i = 0; i < n; i++){
		fd = open(files[i], O_RDONLY);
		check_error(fd, "open");
		size = lseek(fd, 0, SEEK_END);
		check_error(size, "lseek");
		res = lseek(fd, 0, SEEK_SET);
		check_error(res, "lseek");
		strcpy(file_pathname, files[i]);
		res = write(fd_archive, file_pathname, FILEHEADER_LEN);
		check_error(res, "write");
		res = write(fd_archive, &size, sizeof(size));
		check_error(res, "write");
		copy_file(fd_archive, fd);
		res = close(fd);
		check_error(res, "close");
	}
	res = close(fd_archive);
	check_error(res, "close");	
}
