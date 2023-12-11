#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

class RequestManager : public QObject
{
    Q_OBJECT
public:
    explicit RequestManager(QObject *parent = nullptr);
    void sendRequest(const QString &url);

signals:
    void responseReceived(const QString &response);

private slots:
    void onRequestFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    QList<QNetworkReply *> currentReplies;

};

#endif // REQUESTMANAGER_H
