//
// Created by wmatveev on 25.06.2024.
//

#ifndef WSCAN_HTTPCONTROLLER_HPP
#define WSCAN_HTTPCONTROLLER_HPP


#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>


class HttpController : public QObject
{
    Q_OBJECT

    public:
        explicit HttpController(QObject *parent = nullptr);

    void SendSignalToDevice(const QString &url);
    void ActivateScannerRelay();
    void DeactivateScannerRelay();

private slots:
    void onRequestFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    QNetworkAccessManager* getNetworkManager();

};


#endif //WSCAN_HTTPCONTROLLER_HPP
