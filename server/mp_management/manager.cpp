
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <limits.h>
#include <algorithm>

#include "manager.h"
#include "fileutils.h"

#include "error_handler.h"
//------------------------------------------------------------------------------

Manager *Manager::m_instance = nullptr;

//------------------------------------------------------------------------------

//==============================================================================
//
//==============================================================================
Manager* Manager::instance() {
    if (!m_instance) m_instance = new Manager();
    return m_instance;
}

//==============================================================================
//
//==============================================================================
Manager::Manager() {
    const int n_cores = get_nprocs();
    for (int i = 0; i < n_cores; i++) {
	m_workers.push_back(new Worker());
    }
}

//==============================================================================
//
//==============================================================================
int dbg_counter = 0;

int Manager::init() {
//    printf("Master pid: %d [%d]\r\n", getpid(), ++dbg_counter);
    initWorkerMonitoring();
    for (auto w : m_workers) {
	if (w->init() < 0) {
	    fprintf_mp(stderr, "Worker creation error!");
	    return -1;
	}
//	printf(" Worker with PID %d successfully created!\r\n", w->pid());
//	fflush(stdout);
    }    
    return 0;
}

//==============================================================================
//
//==============================================================================
Worker* Manager::getLeastBusyWorker() {
    #if 1
    auto a = std::min_element(m_workers.begin(), m_workers.end(), [](auto a, auto b){return a->CpuUsage() < b->CpuUsage();});
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
//	printf("Worker %d killed!\r\n", w->pid());
    }
    return 0;
}

//==============================================================================
//
//==============================================================================
void Manager::checkWorkersHandler(int sig) {

//    printf("MyPid: %d\r\n", getpid());
//    fflush(stdout);
//    alarm(1);

    Manager *manager = Manager::instance();

    for (auto p : manager->m_workers) {
	if (p->pid() > 0) {
	    if (p->calcCpuUsage() < 0) {
		continue;
	    }
	}
    }
    alarm(1);
}

//==============================================================================
//
//==============================================================================
int Manager::initWorkerMonitoring() {
    struct sigaction sa;

    sa.sa_handler = &Manager::checkWorkersHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        fprintf_mp(stderr, "sigaction SIGALRM");
        return -1;
    }
    alarm(1);
    return 0;
}














