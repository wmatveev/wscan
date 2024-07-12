//
// Created by wmatveev on 12.07.2024.
//

#ifndef WSCAN_PORTPOLLING_HPP
#define WSCAN_PORTPOLLING_HPP


#include <QObject>
#include "HttpController.hpp"

class PortPolling : public QObject
{
    Q_OBJECT

    public:
        explicit PortPolling(QObject *parent = nullptr);

    public:
        void PollFirstPort();

    private:
        HttpController *m_http = nullptr;

        QString cmdPollFirstPort = "RD,1";
        QString url = "http://192.168.45.195/cmd.cgi?psw=Laurent&cmd=";
};


#endif //WSCAN_PORTPOLLING_HPP
