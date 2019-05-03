#ifndef WORKER_H
#define WORKER_H

#include <sys/types.h>
#include <poll.h>
#include <vector>

#include "server.h"

class Worker
{
    static const int PARENT_SIDE = 0;
    static const int CHILD_SIDE = 1;

public:
    Worker();
    int init();

    /* Handle the main loop in worker's own process */
    int child_loop();

    int start(int fd);

    /* Notify the manager that socket processing is done */
    int done(int fd);

    size_t jobs() const { return m_njobs; }
    pid_t pid() const { return m_pid; }
private:
    size_t  m_njobs; // Num of jobs (sockets) doing by the worker
    pid_t   m_pid;
    int     m_sv[2];

    std::vector<pollfd> m_poll_fds;

    HttpServer m_server;
};

#endif // WORKER_H
