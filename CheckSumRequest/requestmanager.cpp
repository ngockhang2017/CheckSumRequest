#include "requestmanager.h"

RequestManager::RequestManager(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &RequestManager::onRequestFinished);
}

void RequestManager::sendRequest(const QString &url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
//    QNetworkRequest request(QUrl(url));
    QNetworkReply *reply = networkManager->get(request);

    // Lưu trữ thông tin về reply để theo dõi khi response về
    currentReplies.append(reply);
}

void RequestManager::onRequestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // Đọc response và gửi tín hiệu
        QString response = reply->readAll();
        emit responseReceived(response);
    } else {
        qDebug() << "Error:" << reply->errorString();
    }

    // Loại bỏ reply đã hoàn thành để tránh rò rỉ bộ nhớ
    currentReplies.removeOne(reply);
    reply->deleteLater();
}
