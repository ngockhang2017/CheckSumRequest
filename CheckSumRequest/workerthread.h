#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include<qthread.h>
#include<QDebug>

class WorkerThread : public QThread
{
public:
    WorkerThread();
    void run() override {
           // Thực hiện công việc trong đây
           for (int i = 0; i < 5; ++i) {
               qDebug() << "Thread" << currentThreadId() << "Working" << i;
               sleep(1); // Simulate work
           }
       }
};

#endif // WORKERTHREAD_H
