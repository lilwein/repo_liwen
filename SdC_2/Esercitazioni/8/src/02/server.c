#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>  // htons()
#include <netinet/in.h> // struct sockaddr_in
#include <sys/socket.h>

#include "common.h"

// Method for processing incoming requests. The method takes as argument
// the socket descriptor for the incoming connection.
void* connection_handler(int socket_desc) {    
    int ret, recv_bytes;

    char buf[1024];
    size_t buf_len = sizeof(buf);
    int msg_len;
    memset(buf,0,buf_len);


    char* quit_command = SERVER_COMMAND;
    size_t quit_command_len = strlen(quit_command);

    // echo loop
    while (1) {
        /** INSERT CODE TO RECEIVE A MESSAGE FROM THE CLIENT
         *
         * Suggestions:
         * - recvfrom() with flags = 0 is equivalent to read() from a descriptor
         * - store the number of received bytes in recv_bytes
         * - for sockets, we get a 0 return value only when the peer closes
         *   the connection: if there are no bytes to read and we invoke
         *   recvfrom() we will get stuck, because the call is blocking!
         * - in UDP we don't deal with partially sent messages, but we manage other errors
         */
         */

        // check if either I have just been told to quit...
        /** TODO: check if the quit_command is received
         *  TODO: in this case we have to quit
         *
         * Suggestions:
         * - compare the number of bytes received with the length of the
         *   quit command that tells the server to close the connection
         *   (see SERVER_COMMAND macro in common.h)
         * - perform a byte-to-byte comparsion when required using
         *   memcmp(const void *ptr1, const void *ptr2, size_t num)
         * - exit from the cycle when there is nothing to send back
         */


        // ...or I have to send the message back
        /** INSERT CODE TO ECHO THE RECEIVED MESSAGE BACK TO THE CLIENT
         * TODO: echo the received message back to the client
         *
         *
         * Suggestions:
         * - sendto() with flags = 0 is equivalent to write() on a descriptor
         * - don't deal with partially sent messages, but manage other errors
         * - message size IS NOT buf size
         */
    }

    // close socket
    ret = close(socket_desc);
    if(ret) {
        handle_error("Cannot close socket for incoming connection");
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    int ret;

    int socket_desc, client_desc;

    // some fields are required to be filled with 0
    struct sockaddr_in server_addr = {0}, client_addr = {0};

    int sockaddr_len = sizeof(struct sockaddr_in); // we will reuse it for accept()

    /** TODO: Create a socket for listening
     *
     * Suggestions:
     * - protocollo AF_INET
     * - tipo SOCK_DGRAM
     */

    /* We enable SO_REUSEADDR to quickly restart our server after a crash:
     * for more details, read about the TIME_WAIT state in the TCP protocol */
    int reuseaddr_opt = 1;
    ret = setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_opt, sizeof(reuseaddr_opt));
    if(ret) {
        handle_error("Cannot set SO_REUSEADDR option");
    }

    /** [SOLUTION]
     *  TODO: set server address and bind it to the socket
     *
     * Suggestions:
     * - set the 3 fields of server:
     * - - server_addr.sin_addr.s_addr: we want to accept connections from any interface
     * - - server_addr.sin_family,
     * - - server_addr.sin_port (using htons() method)
     * - bind address to socket
     * - - attention to the bind method:
     * - - it requires as second field struct sockaddr* addr, but our address is a struct sockaddr_in, hence we must cast it (struct sockaddr*) &server_addr
     */


    // loop to handle incoming connections (sequentially)
    while (1) {
		// accept an incoming connection
        if (DEBUG) fprintf(stderr, "opening connection handler...\n");

        connection_handler(socket_desc);
    }

    exit(EXIT_SUCCESS); // this will never be executed
}
