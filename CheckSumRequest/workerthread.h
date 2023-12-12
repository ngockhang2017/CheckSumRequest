#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include<qthread.h>
#include<QDebug>

class WorkerThread : public QThread
{
public:
    WorkerThread();
    void run() override;
};

#endif // WORKERTHREAD_H
