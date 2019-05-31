#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include "worker.h"

class Manager
{
public:
    static Manager* instance();
    int init();  /* Prefork all the workers here */
    Worker* getLeastBusyWorker();

    int do_work(int fd);
    void recvFromWorker(int fd);

    int killAll();
public:
    static int initWorkerMonitoring();
    static void checkWorkersHandler(int sig);

private:
    Manager();

    static Manager *m_instance;
private:
    std::vector<Worker*> m_workers;
};

#endif // MANAGER_H
