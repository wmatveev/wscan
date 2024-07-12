//
// Created by wmatveev on 12.07.2024.
//

#include <QTimer>
#include "ScanApplication.hpp"
#include "PortPolling.hpp"
#include "ScannerController.hpp"
#include "TrafficLightController.hpp"

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
    auto *scannerController = new ScannerController();
    auto *trafficLightController = new TrafficLightController();

    connect(timer, &QTimer::timeout, this, [this, portPolling]() {
        portPolling->PollFirstPort();
        qDebug() << "PollFirstPort call count:" << ++pollCounter;
    });

    timer->start(100);

    // Timer for activating scanner relay every 500 ms
    auto *activateScannerTimer = new QTimer(this);
    connect(activateScannerTimer, &QTimer::timeout, scannerController, &ScannerController::ActivateScannerRelay);
    activateScannerTimer->start(500);

    // Timer for deactivating scanner relay every 500 ms
    auto *deactivateScannerTimer = new QTimer(this);
    connect(deactivateScannerTimer, &QTimer::timeout, scannerController, &ScannerController::DeactivateScannerRelay);
    deactivateScannerTimer->start(500);

    // Timer for green light every 250 ms
    auto *greenLightTimer = new QTimer(this);
    connect(greenLightTimer, &QTimer::timeout, trafficLightController, &TrafficLightController::GreenLight);
    greenLightTimer->start(250);
}
