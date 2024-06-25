//
// Created by wmatveev on 25.06.2024.
//

#include "HttpController.hpp"
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>


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

void HttpController::ActivateScannerRelay()
{
    QUrl qurl("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd=REL,1,1");

    QNetworkRequest request(qurl);
    QNetworkReply *reply = getNetworkManager()->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Relay activated";
        } else {
            qDebug() << "Failed to activate relay:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void HttpController::DeactivateScannerRelay()
{
    QUrl qurl("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd=REL,1,0");

    QNetworkRequest request(qurl);
    QNetworkReply *reply = getNetworkManager()->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Relay deactivated";
        } else {
            qDebug() << "Failed to deactivate relay:" << reply->errorString();
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