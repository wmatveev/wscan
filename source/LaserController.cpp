//
// Created by wmatveev on 24.06.2024.
//

#include "LaserController.hpp"


LaserController::LaserController(QObject *parent)
        : QObject{parent},
          m_timer{new QTimer(this)},
          m_scanner{new ScannerController},
          m_portsController{new PortsController},
          m_scaleController{new ScaleController},
          m_trafficlightController{new TrafficLightController},
          m_rs232Controller{new RS232Controller},
          m_dataBaseController{new DataBaseController},
          m_hasBarcode{false},
          m_hasWeight{false}
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
    m_timer->start(500);
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
    qDebug() << "[Barcode]:" << data;
    m_portsController->stopReading();

    if (data == m_previousBarcodeData) {
        qDebug() << "Duplicate barcode detected. Skipping database insertion.";
        return;
    }

    m_barcodeData = data;
    m_previousBarcodeData = data;\

    m_trafficlightController->GreenLight();
    m_scanner->DeactivateScannerRelay();

    m_hasBarcode  = true;

    TryInsertDataToDB();
}

void LaserController::onGetWeight(const float &weight)
{
    m_weightData = weight;
    m_hasWeight  = true;

    TryInsertDataToDB();
}

void LaserController::TryInsertDataToDB()
{
    if (m_hasBarcode && m_hasWeight && m_weightData < 20.0f)
    {
        m_hasBarcode = false;
        m_hasWeight  = false;
    }
    else
    {
        if (m_hasBarcode && m_hasWeight)
        {
            QString barcodeStr = QString("%1").arg(QString::fromUtf8(m_barcodeData));

            QString queryString = QString("INSERT INTO production_history (barcode, weight) VALUES ('%1', %2)")
                    .arg(barcodeStr)
                    .arg(m_weightData);

            m_dataBaseController->ExecuteSQLQuery(queryString);


            m_rs232Controller->SendBarcodeToRS232(barcodeStr);

            m_hasBarcode = false;
            m_hasWeight  = false;
        }
    }
}

