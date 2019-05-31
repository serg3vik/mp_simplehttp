#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
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

#include "error_handler.h"

//==============================================================================
static const uint16_t DEFAULT_SERVER_PORT = 8888;

//==============================================================================

const char *RootPath = nullptr;

//==============================================================================
//
//==============================================================================
void signalHandler(int sig) {

    if (sig == SIGTERM) {
	fprintf_mp(stdout, "Kill \'em ALL!\n");
	Manager::instance()->killAll();
	deinitLog();
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
struct globalArgs_t {
    const char *ipaddr;
    const char *port;
    const char *root_dir;
} globalArgs;

static const char *optString = "h:p:d:";
//==============================================================================
// Launch options: -h <ip> -p <port> -d <directory>
//==============================================================================
int main(int argc, char *argv[]) {

    #if defined DAEMON_APP
    /* DAEMONIZE */
    pid_t pid, sid;

    fprintf(stdout, "Alive @ %d!\r\n", __LINE__);
    fflush(stdout);

    /* Fork off the parent process */
    pid = fork();
    fprintf(stdout, "Alive @ %d!\r\n", __LINE__);
    fflush(stdout);
    if (pid < 0) {
	perror("daemonize fork");
	exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
       we can exit the parent process. */
    if (pid > 0) {
	exit(EXIT_SUCCESS);
    }
    fprintf(stdout, "Alive @ %d!\r\n", __LINE__);
    fflush(stdout);
    /* Change the file mode mask */
    umask(0);

    fprintf(stdout, "Alive @ %d!\r\n", __LINE__);
    fflush(stdout);
    /* Open any logs here */
    if (initLog() < 0) {
	perror("Init LOG");
	exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Alive @ %d!\r\n", __LINE__);
    fflush(stdout);
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
	/* Log any failure here */
	perror("setsid");
	exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
	/* Log any failure here */
	perror("chdir");
	exit(EXIT_FAILURE);
    }


    fprintf_mp(stdout, "Helloworld epta!\r\n");


    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

   /* end of daemonize */
    #else
    initLog();
    #endif

    memset (&globalArgs, 0, sizeof(globalArgs_t));
    int opt;
    while((opt = getopt(argc, argv, optString)) != -1) {
	switch (opt) {
	    case 'h': {
		globalArgs.ipaddr = optarg;
	    }break;
	    case 'p': {
		globalArgs.port = optarg;
	    }break;
	    case 'd': {
		globalArgs.root_dir = optarg;
	    }
	}
    }

    if (!(globalArgs.ipaddr && globalArgs.port && globalArgs.root_dir)) return -1;

    RootPath = globalArgs.root_dir;
    uint16_t ServerPort;
    sscanf(globalArgs.port, "%d", &ServerPort);

    struct sigaction sa;
    int rv = -1;
    int opt_enable = 1;

    Manager *manager = Manager::instance();
    if (!manager) {
	return -1;
	fprintf_mp(stderr, "Can\'t create the manager!");
    }

    sa.sa_handler = signalHandler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
	fprintf_mp(stderr, "sigaction SIGCHLD");
        return -1;
    }
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
	fprintf_mp(stderr, "sigaction SIGTERM");
        return -1;
    }

    int MasterSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (MasterSocket < 0) {
   	fprintf_mp(stderr, "Socket creation failed! %s", strerror(errno));
	return EXIT_FAILURE;
    }

    if (setsockopt(MasterSocket, SOL_SOCKET, SO_REUSEADDR, &opt_enable, sizeof(int)) == -1) {
	fprintf_mp(stderr, "setsockopt %s", strerror(errno));
	return -1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr	= INADDR_ANY;
    serv_addr.sin_family	= AF_INET;
    serv_addr.sin_port		= htons(ServerPort);

    if (bind(MasterSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	fprintf_mp(stderr, "server: bind %s", strerror(errno));
	return -1;
    }

    manager->init();

    if (listen(MasterSocket, SOMAXCONN) < 0) {
	fprintf_mp(stderr, "server: listen");
	return -1;
    }

    /* Main server loop */
    while (1) {
	int SlaveSocket = accept(MasterSocket, NULL, NULL);
	if (SlaveSocket < 0) {
	    fprintf_mp(stderr, "server: accept");
	    return -1;
	}
	if (manager->do_work(SlaveSocket) == -1) {
	    fprintf_mp(stderr, "do_work");
	    return -1;
	}
    }
    /* THE PARENT PROCESS MUST STILL ALIVE UNTIL AT LEAST ONE CHILD IS ALIVE! */

    deinitLog();
    return 0;
}
