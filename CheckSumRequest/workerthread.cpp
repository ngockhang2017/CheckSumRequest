#include "workerthread.h"

WorkerThread::WorkerThread(const QString &url, QObject *parent)
    : QThread(parent), url(url)
{

}

void WorkerThread::run() {
    QNetworkAccessManager manager;
    QUrl url_address = QUrl(url);
    QNetworkRequest request(url_address);

    // Thực hiện request HTTP
    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Kiểm tra kết quả
    if (reply->error() == QNetworkReply::NoError) {
        emit success(reply->readAll());
    } else {
        emit fail(reply->errorString());
    }
    reply->deleteLater();
}
