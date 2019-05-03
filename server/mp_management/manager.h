#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include "worker.h"

class Manager
{
public:
    Manager();
    int init();  /* Prefork all the workers here */
    Worker* getLeastBusyWorker();

    int do_work(int fd);
    void recvFromWorker(int fd);

    int killAll();

private:
    std::vector<Worker*> m_workers;
};

#endif // MANAGER_H
