//
// Created by wmatveev on 02.07.2024.
//

#ifndef WSCAN_RS232CONTROLLER_HPP
#define WSCAN_RS232CONTROLLER_HPP


#include <QObject>
#include <QDebug>
#include "HttpController.hpp"

class RS232Controller  : public QObject
{
    Q_OBJECT

    public:
        explicit RS232Controller(QObject *parent = nullptr);

    public:
        void SendBarcodeToRS232(const QString& barcode);

    private:
        HttpController *m_http = nullptr;
        QString cmdSendBarcodeToRS232 = "PUT,U,C,";
        QString url = "http://192.168.45.195/cmd.cgi?psw=Laurent&cmd=";
};


#endif //WSCAN_RS232CONTROLLER_HPP
