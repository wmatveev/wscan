//
// Created by wmatveev on 24.06.2024.
//

#include <QDebug>
#include "LaserController.hpp"
#include "HttpController.hpp"


LaserController::LaserController(ScannerController *scanner, QObject *parent)
        : QObject{parent},
          m_timer{new QTimer(this)},
          m_scanner{scanner}
{
    m_timer->setSingleShot(true);

    connect(m_timer, &QTimer::timeout, this, [this]() {
        HttpController::ActivateScannerRelay(QString("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd="));

        QByteArray barcode = m_scanner->GetBarcode();
        if (!barcode.isEmpty()) {
            qDebug() << "Barcode data:" << barcode;
        } else {
            qDebug() << "No barcode data received";
        }

        HttpController::DeactivateScannerRelay(QString("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd="));

        qDebug() << "Timer timeout - 3 seconds elapsed";
    });
}

void LaserController::onLaserTriggered(unsigned char data)
{
    qDebug() << "Laser triggered with data:" << data;
    m_timer->start(10);
}

void LaserController::onLaserReleased(unsigned char data)
{
    qDebug() << "Laser released with data:" << data;
    if (m_timer->isActive()) {
        m_timer->stop();
        qDebug() << "Timer stopped";
    }
}

