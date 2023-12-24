#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include <QCoreApplication>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include<QElapsedTimer>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(const QString& url, QObject *parent = nullptr);

signals:
    void success(const QString& str, int rtt);
    void fail(const QString& str);

protected:
    void run() override;

private:
    QString url;
    QElapsedTimer timer;
};

#endif // WORKERTHREAD_H
