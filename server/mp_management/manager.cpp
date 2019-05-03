
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include "manager.h"

//==============================================================================
//
//==============================================================================
Manager::Manager() {
    const int n_cores = 1;//get_nprocs();
    for (int i = 0; i < n_cores; i++) {
	m_workers.push_back(new Worker());
    }
}

//==============================================================================
//
//==============================================================================
int dbg_counter = 0;

int Manager::init() {
    printf("Master pid: %d [%d]\r\n", getpid(), ++dbg_counter);
    for (auto w : m_workers) {
	if (w->init() < 0) {
	    fprintf(stderr, "Worker creation error!");
	    return -1;
	} else {
	    printf(" Worker with PID %d successfully created!\r\n", w->pid());
	    fflush(stdout);
	}
    }
    return 0;
}

//==============================================================================
//
//==============================================================================
Worker* Manager::getLeastBusyWorker() {
    #if 0
    auto a = std::min_element(m_workers.begin(), m_workers.end(), [](auto a, auto b){return a->jobs() < b->jobs();});
    return *a;
    #else
    return m_workers.at(0); // For DEBUG only!
    #endif
}

//==============================================================================
//
//==============================================================================
int Manager::do_work(int fd) { // Parent process
    Worker *w = getLeastBusyWorker();
    if (w) {
	return w->start(fd);
    } else {
	return -1;
    }
}

//==============================================================================
//
//==============================================================================
int Manager::killAll() {
    for (auto w : m_workers) {
	kill(w->pid(), SIGKILL);
	int status;
	wait(&status);
	printf("Worker %d killed!\r\n", w->pid());
    }
    return 0;
}














