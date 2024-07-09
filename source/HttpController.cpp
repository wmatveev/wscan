//
// Created by wmatveev on 25.06.2024.
//

#include "HttpController.hpp"
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>


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

void HttpController::SendSignalToDevice(const QString &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = getNetworkManager()->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
        } else {
            qDebug() << "Failed to send data:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void HttpController::SendBinaryDataToDevice(const QString &url, const QByteArray &data)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    qDebug() << "[url}: "  << url;
    qDebug() << "[data}: " << data;

    QNetworkReply *reply = getNetworkManager()->post(request, data);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Data sent successfully";
        } else {
            qDebug() << "Failed to send data:" << reply->errorString();
        }
        reply->deleteLater();
    });
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
