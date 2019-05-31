#ifndef WORKER_H
#define WORKER_H

#include <sys/types.h>
#include <poll.h>
#include <vector>
#include <unordered_map>

#include "server.h"

//------------------------------------------------------------------------------

struct proc_times_t {
    unsigned long utime;
    unsigned long totaltime;
};

//------------------------------------------------------------------------------

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

    /* Set and get CPU usage value. It must used in manager process only! */
    int CpuUsage() const { return m_cpu_usage; }
    void setCpuUsageValue(int val);

    pid_t pid() const { return m_pid; }

    int calcCpuUsage();
private:
    int	    m_cpu_usage; // Total CPU usage
    pid_t   m_pid;
    int     m_sv[2];

    proc_times_t m_proc_times_old;

    std::unordered_map<int, pollfd> m_pfds;

    HttpServer m_server;
};

#endif // WORKER_H
