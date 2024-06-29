//
// Created by wmatveev on 24.06.2024.
//

#include <QDebug>
#include "LaserController.hpp"


LaserController::LaserController(QObject *parent)
        : QObject{parent},
          m_timer{new QTimer(this)},
          m_scanner{new ScannerController},
          m_portsController{new PortsController},
          m_scaleController{new ScaleController},
          m_trafficlightController{new TrafficLightController}
{
    m_trafficlightController->BlueLight();
    m_timer->setSingleShot(true);

    connect(m_timer, &QTimer::timeout, this, [this]() {
        m_trafficlightController->RedLight();

        // Reading ports and waiting barcode
        m_portsController->start();
        m_scaleController->start();

        m_scanner->ActivateScannerRelay();
    });

    connect(m_portsController, &PortsController::dataReadyForRead, this, &LaserController::onGetBarcode);
    connect(m_scaleController, &ScaleController::weightReadyForRead, this, &LaserController::onGetWeight);
}

void LaserController::onLaserTriggered(unsigned char data)
{
    m_timer->start(3000);
    m_trafficlightController->YellowLight();
}

void LaserController::onLaserReleased(unsigned char data)
{
    if (m_timer->isActive()) {
        m_timer->stop();
        qDebug() << "Timer stopped";
    }

    m_scanner->DeactivateScannerRelay();
    m_trafficlightController->BlueLight();
}

void LaserController::onGetBarcode(const QByteArray &data)
{
    qDebug() << "Received barcode data:" << data;
    m_portsController->stopReading();

    m_trafficlightController->GreenLight();
    m_scanner->DeactivateScannerRelay();
}

void LaserController::onGetWeight(const QVector<int> &weight)
{

}
