
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "worker.h"
#include "fd_pass.h"
#include "error_handler.h"


//==============================================================================
//
//==============================================================================
Worker::Worker() :
    m_cpu_usage(0),
    m_pid(-1),
    m_sv{-1, -1},
    m_proc_times_old{0, 0}
    {
    }

//==============================================================================
//
//==============================================================================
int Worker::init() {
    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, m_sv) < 0) {
	fprintf_mp(stderr, "worker socketpair\r\n");
	return -1;
    }
    switch ((m_pid = fork())) {
    case 0:
	/* child process */
	close(m_sv[PARENT_SIDE]);
	alarm(0);
	return child_loop();
	break;
    case -1:
	fprintf_mp(stderr, "worker fork\r\n");
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
int Worker::child_loop() { // Executes in it's own process! Should never return!

    char    buf[16];

    /* Interprocess communication socket */
    const int &ipc_socket = m_sv[CHILD_SIDE];

    std::vector<pollfd> active_pfds;

    sleep(1);
    while(1) {
	/* Clear the vector first */
	active_pfds.clear();
	/* First, write the IPC socket to poll queue vector */
	active_pfds.push_back({.fd = ipc_socket, .events = POLLIN, .revents = 0});
	/* Then, write all of the rest */
	for (auto a : m_pfds) {
	    active_pfds.push_back(a.second);
	}

	int pfd = poll(active_pfds.data(), active_pfds.size(), -1);
	if (pfd < 0) {
	    fprintf_mp(stderr, "poll\r\n");
	    return -2;
	}

//	fprintf_mp(stdout, "Poll passed [pid: %d]!\r\n", getpid());
	int c = 0;
	for (auto p : active_pfds) {
//	    printf(":%d: %d | 0x%08X | 0x%08X\r\n", c++, p.fd, p.events, p.revents);
	}
//	fflush(stdout);

	/* Manager socket handling */
	pollfd &mgr_poll_fd = active_pfds.at(0);
	if ( mgr_poll_fd.revents & POLLIN ) {
	    mgr_poll_fd.revents = 0;
//	    std::cout << "Got NEW!" << std::endl << std::flush;
	    int fd;
	    ssize_t size = sock_fd_read(mgr_poll_fd.fd, buf, sizeof(buf), &fd);
	    if (size < 0) {
		return -2;
	    } else if (size == 0) {
		continue;
	    }
//	    printf ("read fd# %d\n", fd);
//	    fflush(stdout);
	    /* Got new valid socket fd? */
	    if (fd != -1) {	
//		std::cout << "Adding new!" << std::endl << std::flush;
		/* Add new item to poll queue map */
		m_pfds[fd] = {.fd = fd, .events = POLLIN, .revents = 0};
//		m_pfds.insert(std::make_pair<int, pollfd>(fd, {.fd = fd, .events = POLLIN, .revents = 0}));
	    }
	}


	for (int i = 1; i < active_pfds.size(); i++) {
	    pollfd &client_poll_fd = active_pfds.at(i);
	    if (client_poll_fd.revents & POLLIN) {
		client_poll_fd.revents = 0;
		const int client_fd = client_poll_fd.fd;
		/* Do something with it */
		m_server.handleClientConection(client_fd);

		/* Close the socket */
		if (shutdown(client_fd, SHUT_RDWR) < 0) {
            fprintf_mp(stderr, "shutdown\r\n");
		    return -1;
		}
		if (close(client_fd) < 0) {
		    fprintf_mp(stderr, "close\r\n");
		    return -1;
		}

		/* And remove it from poll map */
		m_pfds.erase(client_fd);
//		client_poll_fd.events = 0;
//		printf("Done with socket [%d]\r\n", client_poll_fd.fd);
//		fflush(stdout);
	    }
	    if (client_poll_fd.revents & POLLNVAL) {
//		fprintf(LOG_FILE, "POLLNVAL at [%d]\r\n",client_poll_fd.fd );
		client_poll_fd.revents = 0;
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
//    printf ("wrote %d\n", size);
    return 0;
}

//==============================================================================
//
//==============================================================================
void Worker::setCpuUsageValue(int val) {
    m_cpu_usage = val;
}

//==============================================================================
// Must be called from manager process!
//==============================================================================
int Worker::calcCpuUsage() {

    char stat_path[32] = {0};
    const char *cpu_file_path = "/proc/stat";
    const ssize_t STAT_MAX_SIZE = 1024;
    const int UTIME_POS = 13;

    proc_times_t proc_times_current = {.utime = 0, .totaltime = 0};

    std::unique_ptr<char[]> stat_buf = std::unique_ptr<char[]>(new char[STAT_MAX_SIZE]);
    memset(stat_buf.get(), 0, STAT_MAX_SIZE);

    FILE *cpu_stat_file = fopen(cpu_file_path, "r");
    fseek(cpu_stat_file, 4, SEEK_SET); // skip the "cpu " at the beginning of the file
    for (int i = 0; i < 10; i++) {
	unsigned long cpu_time;
	fscanf(cpu_stat_file, "%lu", &cpu_time);
	proc_times_current.totaltime += cpu_time;
    }
    fclose(cpu_stat_file);

    sprintf(stat_path, "/proc/%d/stat", this->pid());
    stat_path[31] = '\0';
    FILE *stat_file = fopen(stat_path, "r");
    if (!stat_file) {
//	fprintf(LOG_FILE, "Process with pid=%d doesn\'t exists! %s\r\n",  this->pid(), stat_path);
	fprintf_mp(stderr, "Process with desired PID does not exist!\r\n");
	return -1;
    }

    char *stat_buf_str = stat_buf.get();

    char c;
    while ((c = fgetc(stat_file)) != EOF) {
	*(stat_buf_str++) = c;
    }
//	    size_t read_size = std::min(stat_size, STAT_MAX_SIZE);
//	    fread(stat_buf_str, 1, read_size, stat_file);
    fclose(stat_file);

    char *pch = stat_buf.get();

    const char *needle = " ";
    for (int i = 0; i < UTIME_POS; i++) {
	if (pch) {
	    pch = strstr(pch + 1, needle);
	} else {
//	    fprintf(LOG_FILE, "ACHTUNG! pch becames NULL at %d pos!\r\n", i);
	    fprintf_mp(stderr, "ACHTUNG! pch is NULL!\r\n");
	}
    }
    if (!pch) return -1;

    if (sscanf(pch, "%lu", &proc_times_current.utime) < 0) {
	fprintf_mp(stderr, "sscanf\r\n");
	return -1;
    }


//	    user_util = 100 * (utime_after - utime_before) / (time_total_after - time_total_before);
//	    sys_util = 100 * (stime_after - stime_before) / (time_total_after - time_total_before);
    int user_util = 100 * (proc_times_current.utime - m_proc_times_old.utime) / (proc_times_current.totaltime - m_proc_times_old.totaltime);

    m_proc_times_old = proc_times_current;

    this->setCpuUsageValue(user_util);
    return 0;
}








