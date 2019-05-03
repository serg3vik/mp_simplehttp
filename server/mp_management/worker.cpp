
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "worker.h"
#include "fd_pass.h"

//==============================================================================
//
//==============================================================================
Worker::Worker() :
    m_njobs(0),
    m_pid(-1),
    m_sv{-1, -1}
    {
    }

//==============================================================================
//
//==============================================================================
int Worker::init() {
    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, m_sv) < 0) {
	perror("socketpair");
	return -1;
    }
    switch ((m_pid = fork())) {
    case 0:
	/* child process */
	close(m_sv[PARENT_SIDE]);
	return child_loop();
	break;
    case -1:
	perror("fork");
	return -1;
    default:
	/* parent process */
	close(m_sv[CHILD_SIDE]);
//      return m_parent_socket; ///////
	return 0;
	break;
    }
    return -1; // Should never get here
}

//==============================================================================
//
//==============================================================================
int Worker::child_loop() { // Executes in it's own process! Should newer return!
    int fd;
    char    buf[16];


    m_poll_fds.push_back({.fd = m_sv[CHILD_SIDE], .events = POLLIN, .revents = 0});

    sleep(1);
    while(1) {
	int pfd = poll(m_poll_fds.data(), m_poll_fds.size(), -1);
	if (pfd < 0) {
	    perror("poll");
	    return -2;
	}

	/* Manager socket handling */
	pollfd &mgr_poll_fd = m_poll_fds.at(0);
	if ( mgr_poll_fd.revents & POLLIN ) {
	    mgr_poll_fd.revents = 0;

	    ssize_t size = sock_fd_read(mgr_poll_fd.fd, buf, sizeof(buf), &fd);
	    if (size < 0) {
		return -2;
	    } else if (size == 0) {
		continue;
	    }
	    printf ("read %d\n", size);
	    if (fd != -1) { /* Got valid fd? */
		/* Add it to pollfd vector */
		m_poll_fds.push_back({.fd = fd, .events = POLLIN, .revents = 0});
	    }
	}

	for (int i = 1; i < m_poll_fds.size(); i++) {
	    pollfd &client_poll_fd = m_poll_fds.at(i);
	    if (client_poll_fd.revents & POLLIN) {
		client_poll_fd.revents = 0;
		/* Do something with it */
		m_server.readFromSocket(client_poll_fd.fd);
	    }
	}
    }
    return 0;
}


//==============================================================================
//
//==============================================================================
int Worker::start(int fd) { // Parent process
    ssize_t size = sock_fd_write(m_sv[PARENT_SIDE], "1", 1, fd);
    printf ("wrote %d\n", size);
    return 0;
}









