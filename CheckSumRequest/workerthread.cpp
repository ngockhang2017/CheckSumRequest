#include "workerthread.h"

WorkerThread::WorkerThread(const QString &url, QObject *parent)
    : QThread(parent), url(url)
{

}

void WorkerThread::run()
{
    QNetworkAccessManager manager;
    QUrl url_address = QUrl(url);
    QNetworkRequest request(url_address);

    // Thực hiện request HTTP
    timer.start();
    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Kiểm tra kết quả
    if (reply->error() == QNetworkReply::NoError)
    {
        int ThoiGian_Troiqua = timer.elapsed();
        qDebug() << "Thoi gian troi qua la: " << ThoiGian_Troiqua<<endl;
        emit success(reply->readAll()+"; ------ Round trip time: " + QString::number(ThoiGian_Troiqua) + "ms", ThoiGian_Troiqua);
    } else
    {
        emit fail(reply->errorString());
    }
    reply->deleteLater();
}
