#include "workerthread.h"

WorkerThread::WorkerThread()
{
    mRequestManager = new RequestManager();

//    timer_request = new QTimer();
//    connect(timer_request, SIGNAL(timeout()), this, SLOT(request()));
//    timer_request->start(this->timer_ramp_up);
}

void WorkerThread::run() {

    for (int i = 0; i < loop_time; ++i) {
        qDebug() << "Thread" << currentThreadId() << "Working" << i;
        mRequestManager->sendRequest(this->url_str);
        sleep(this->timer_ramp_up);//thực hiện request mỗi timer thời gian (thời gian ramp up)
    }
}

void WorkerThread::request()  //thực hiện request mỗi timer thời gian (thời gian ramp up)
{
//    mRequestManager->sendRequest(this->url_str);
}
