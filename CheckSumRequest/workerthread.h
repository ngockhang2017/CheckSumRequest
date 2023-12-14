#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include <QCoreApplication>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(const QString& url, QObject *parent = nullptr);

signals:
    void success(const QString& str);
    void fail(const QString& str);

protected:
    void run() override;

private:
    QString url;
};

#endif // WORKERTHREAD_H
