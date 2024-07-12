//
// Created by wmatveev on 25.06.2024.
//

#include "HttpController.hpp"
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>
#include <QEventLoop>


HttpController::HttpController(QObject *parent)
        : QObject(parent),
          networkManager(new QNetworkAccessManager(this))
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &HttpController::onRequestFinished);
}

QNetworkAccessManager* HttpController::getNetworkManager()
{
    static QNetworkAccessManager manager;
    return &manager;
}

QByteArray HttpController::SendSignalToDevice(const QString &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = getNetworkManager()->get(request);

    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);

    eventLoop.exec();

    QByteArray responseData;
    if (reply->error() == QNetworkReply::NoError) {
        responseData = reply->readAll();
    } else {
        qDebug() << "Failed to send data:" << reply->errorString();
    }
    reply->deleteLater();

    return responseData;
}

void HttpController::onRequestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Request succeeded";
    } else {
        qDebug() << "Request failed:" << reply->errorString();
    }
    reply->deleteLater();
}
