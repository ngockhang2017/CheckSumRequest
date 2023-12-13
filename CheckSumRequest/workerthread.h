#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include<qthread.h>
#include<QDebug>
#include<QTimer>
#include<requestmanager.h>

class WorkerThread : public QThread
{
public:
    WorkerThread();
    void run() override;
public slots:
    void request();

public:
     int number_of_thread, timer_ramp_up, loop_time;
     QTimer *timer_request;
     RequestManager *mRequestManager;
     QString url_str;
};

#endif // WORKERTHREAD_H
