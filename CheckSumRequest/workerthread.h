#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include<qthread.h>
#include<QDebug>
#include<QTimer>
#include<requestmanager.h>
#include<QString>

class WorkerThread : public QThread
{
public:
    WorkerThread();

    void run() override;

//signals:
// void Susscess(QString str);
// void Fail(QString errorMessage);

public slots:
 void GetReportFromResponse(QString);
 void GetReportFromNon_Response(QString);

public:
    int timer_ramp_up;
    //     QTimer *timer_request;
    RequestManager *mRequestManager;
    QString url_str;
};

#endif // WORKERTHREAD_H
