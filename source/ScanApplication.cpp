//
// Created by wmatveev on 12.07.2024.
//

#include <QTimer>
#include "ScanApplication.hpp"
#include "PortPolling.hpp"

ScanApplication::ScanApplication(QObject *parent)
        : QObject(parent),
          pollCounter{0}
{

}

void ScanApplication::RunApplication()
{
//    ITcpServer  *server = new TcpServer();

    auto *portPolling = new PortPolling();
    auto *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this, portPolling]() {
        portPolling->PollFirstPort();
        qDebug() << "PollFirstPort call count:" << ++pollCounter;
    });

    timer->start(1000);
}
