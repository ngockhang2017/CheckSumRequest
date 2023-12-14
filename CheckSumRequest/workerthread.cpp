#include "workerthread.h"

WorkerThread::WorkerThread()
{
    mRequestManager = new RequestManager();
//    connect(mRequestManager, SIGNAL(responseReceived( QString)), this, SLOT(GetReportFromResponse(QString)));
//    connect(mRequestManager, SIGNAL(responseNon_Received( QString)), this, SLOT(GetReportFromNon_Response(QString)));

    connect(mRequestManager, &RequestManager::responseReceived, this, &WorkerThread::GetReportFromResponse);
    connect(mRequestManager, &RequestManager::responseNon_Received, this, &WorkerThread::GetReportFromNon_Response);
}

void WorkerThread::run()
{
    qDebug() << "Thread" << currentThreadId() << "Working" ;
    mRequestManager->sendRequest(this->url_str);

    sleep(this->timer_ramp_up);//thực hiện 1 request mỗi timer thời gian (thời gian ramp up)
}

void WorkerThread::GetReportFromResponse(QString report)
{
   // emit Susscess(report);
}


void WorkerThread::GetReportFromNon_Response(QString report)
{
   // emit Fail(report);
}

