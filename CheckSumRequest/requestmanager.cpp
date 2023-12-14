#include "requestmanager.h"

RequestManager::RequestManager(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished,this, &RequestManager::onRequestFinished);

     emit responseReceived("responseReceived");
     emit responseNon_Received("Error: responseNon_Received");
}

void RequestManager::sendRequest( QString url)
{
//      QNetworkRequest request(QUrl("http://0.0.0.0:8081/DOA_value.html"));
    QNetworkRequest request;
    request.setUrl(QUrl(url));
//    QNetworkRequest request(QUrl(url));
    QNetworkReply *reply = networkManager->get(request);

    currentReplies.append(reply);
}

void RequestManager::onRequestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)  //   GỬI TÍN HIỆU VỀ MAIN WINDOW --> THÀNH CÔNG
    {
        // Đọc response và gửi tín hiệu
        QString response = reply->readAll();
        emit responseReceived(response);
    }
    else  //GỬI TÍN HIỆU VỀ MAIN WINDOW --> THẤT BẠI
    {
        qDebug() << "Error:" << reply->errorString();
        emit responseNon_Received("Error: " + reply->errorString());
    }

    // Loại bỏ reply đã hoàn thành để tránh rò rỉ bộ nhớ
    currentReplies.removeOne(reply);
    reply->deleteLater();
}
