//
// Created by wmatveev on 12.07.2024.
//

#include <QTimer>
#include "ScanApplication.hpp"
#include "PortPolling.hpp"

ScanApplication::ScanApplication(QObject *parent)
        : QObject(parent)
{

}

void ScanApplication::RunApplication()
{
//    ITcpServer  *server = new TcpServer();

    auto *portPolling = new PortPolling();
    auto *timer = new QTimer(this);
    int pollCounter = 0;

    connect(timer, &QTimer::timeout, this, [portPolling, &pollCounter]() {
        portPolling->PollFirstPort();
        qDebug() << "PollFirstPort call count:" << ++pollCounter;
    });

    timer->start(1000);
}
