//
// Created by wmatveev on 24.06.2024.
//

#include <QDebug>
#include "LaserController.hpp"


LaserController::LaserController(ScannerController *scanner, QObject *parent)
        : QObject{parent},
          m_timer{new QTimer(this)},
          m_scanner{scanner},
          m_portsController{new PortsController},
          m_controller{new HttpController}
{
    m_timer->setSingleShot(true);

    connect(m_timer, &QTimer::timeout, this, [this]() {
        qDebug() << "!---> Start reading ports";
        m_portsController->run();

        qDebug() << "!---> 222";

        m_controller->ActivateScannerRelay();
    });

    connect(m_portsController, &PortsController::dataReadyForRead, this, &LaserController::onGetBarcode);
}

void LaserController::onLaserTriggered(unsigned char data)
{
    qDebug() << "Laser triggered with data:" << data;
    m_timer->start(3000);
}

void LaserController::onLaserReleased(unsigned char data)
{
    qDebug() << "Laser released with data:" << data;
    if (m_timer->isActive()) {
        m_timer->stop();
        qDebug() << "Timer stopped";
    }
}

void LaserController::onGetBarcode(const QByteArray &data)
{
    qDebug() << "Received barcode data:" << data;
    m_portsController->stopReading();

    m_controller->DeactivateScannerRelay();
}

