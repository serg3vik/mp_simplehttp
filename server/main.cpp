#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>

#include "fd_pass.h"
#include "manager.h"

//==============================================================================
static const uint16_t DEFAULT_SERVER_PORT = 8888;

//==============================================================================
static Manager MP_Manager;


//==============================================================================
//
//==============================================================================
void signalHandler(int sig) {

    if (sig == SIGTERM) {
	printf("Kill \'em ALL!\n");

	MP_Manager.killAll();
	exit(1);
    } else {
	// waitpid() might overwrite errno, so we save and restore it:
	int saved_errno = errno;

	while(waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
    }
}

//==============================================================================
//
//==============================================================================

//==============================================================================
//
//==============================================================================
//void child(int sock) {
//    int fd;
//    char    buf[16];
//    ssize_t size;

//    sleep(1);
//    for (;;) {
//        size = sock_fd_read(sock, buf, sizeof(buf), &fd);
//        if (size <= 0)
//            break;
//        printf ("read %d\n", size);
//        if (fd != -1) {
//            write(fd, "hello, world\n", 13);
//            close(fd);
//        }
//    }
//}

//==============================================================================
//
//==============================================================================
//int parent(int int_sock, int ext_sock) {

//    if (listen(ext_sock, SOMAXCONN) < 0) {
//	perror("listen");
//	return -1;
//    }
//    while (1) {
//	int SlaveSocket = accept(ext_sock, NULL, NULL);
//	if (SlaveSocket < 0) {
//	    /* Got incoming connection! */
//	    ssize_t size = sock_fd_write(int_sock, "1", 1, SlaveSocket);
//	    if (size < 0) {
//		perror("sock_fd_write");
//		close(SlaveSocket);
//	    }
//	}

//    }
//    ssize_t size;
//    int i;
//    int fd;

//    fd = 1;
//    size = sock_fd_write(sock, "1", 1, 1);
//    printf ("wrote %d\n", size);
//}

//==============================================================================
//
//==============================================================================
int main(int argc, char *argv[]) {

    struct sigaction sa;
    int rv = -1;
    int opt_enable = 1;

    sa.sa_handler = signalHandler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction SIGCHLD");
        return -1;
    }
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("sigaction SIGTERM");
        return -1;
    }


    int MasterSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (MasterSocket < 0) {
	perror("Socket creation failed!");
	return EXIT_FAILURE;
    }

    if (setsockopt(MasterSocket, SOL_SOCKET, SO_REUSEADDR, &opt_enable, sizeof(int)) == -1) {
	perror("setsockopt");
	return -1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr	= INADDR_ANY;
    serv_addr.sin_family	= AF_INET;
    serv_addr.sin_port		= htons(DEFAULT_SERVER_PORT);

    if (bind(MasterSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	perror("server: bind");
	return -1;
    }

    MP_Manager.init();

    if (listen(MasterSocket, SOMAXCONN) < 0) {
	perror("server: listen");
	return -1;
    }



    /* Beyond this point we have to kill all the children processes first before return/exit! */

    /* Main server loop */
    while (1) {
	int SlaveSocket = accept(MasterSocket, NULL, NULL);
	if (SlaveSocket < 0) {
	    perror("server: accept");

	    return -1;
	}
	MP_Manager.do_work(SlaveSocket);
    }






    /* THE PARENT PROCESS MUST STILL ALIVE UNTIL AT LEAST ONE CHILD IS ALIVE! */
//    pause();

    return 0;
}
