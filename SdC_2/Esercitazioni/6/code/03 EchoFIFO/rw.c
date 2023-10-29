#include <unistd.h>
#include <errno.h>
#include "common.h"


int readOneByOne(int fd, char* buf, char separator) {

    int ret;

    /** [TO DO] READ THE MESSAGE THROUGH THE FIFO DESCRIPTOR
     *
     * Suggestions:
     * - you can read from a FIFO as from a regular file descriptor
     * - since you don't know the length of the message, just
     *   read one byte at a time from the socket
     * - leave the cycle when 'separator' ('\n') is encountered 
     * - repeat the read() when interrupted before reading any data
     * - return the number of bytes read
     * - reading 0 bytes means that the other process has closed
     *   the FIFO unexpectedly: this is an error that should be
     *   dealt with!
     **/

    int bytes_read = 0;

    do {       
        ret = read(fd, buf + bytes_read, 1);
        if(ret==-1){
            if(errno==EINTR) continue;
            handle_error("error on read()");
        }
        if(ret==0) handle_error("Process closed FIFO unexpectedly");

    } while ( buf[bytes_read++] != separator ) ;

    return bytes_read;
}

void writeMsg(int fd, char* buf, int size) {

    int ret;
    /** [TO DO] SEND THE MESSAGE THROUGH THE FIFO DESCRIPTOR
     *
     * Suggestions:
     * - you can write on the FIFO as on a regular file descriptor
     * - make sure that all the bytes have been written: use a while
     *   cycle in the implementation as we did for file descriptors!
     **/

    int bytes_written = 0;

    while ( bytes_written < size ) {       
        ret = write(fd, buf + bytes_written, size);
        if(ret==-1){
            if(errno==EINTR) continue;
            handle_error("error on write()");
        }
        bytes_written += ret;
    }
}
