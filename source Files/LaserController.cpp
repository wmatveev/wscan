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
    m_timer->start(1000);
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

    m_barcodeData = data;

    m_trafficlightController->GreenLight();
    m_scanner->DeactivateScannerRelay();

    m_barcodeData = data;
    m_hasBarcode  = true;

    TryInsertDataToDB();
}

void LaserController::onGetWeight(const float &weight)
{
    m_weightData = weight;
    m_hasWeight  = true;

    TryInsertDataToDB();
}

void LaserController::test()
{
    m_barcodeData = QByteArray::number(123456);;
    m_weightData  = 31.2f;

    m_hasBarcode = m_hasWeight = true;

    TryInsertDataToDB();
}

void LaserController::TryInsertDataToDB()
{
    qDebug() << "---> step1";
    if (m_hasBarcode && m_hasWeight)
    {
        qDebug() << "---> step2";
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("192.168.45.197");
        db.setDatabaseName("w_scan");
        db.setUserName("postgres");
        db.setPassword("Matller_17");

        qDebug() << "---> step3";

        if (!db.open()) {
            qDebug() << "Failed to connect to database:" << db.lastError().text();
            return;
        }

        qDebug() << "---> step4";

        QString barcodeStr = QString::fromUtf8(m_barcodeData);

        QSqlQuery query;
        query.prepare("INSERT INTO production_history (barcode_data, weight_data) VALUES (:barcode_data, :weight_data)");
        query.bindValue(":barcode_data", barcodeStr);
        query.bindValue(":weight_data", m_weightData);

        qDebug() << "---> step5";

        if (!query.exec()) {
            qDebug() << "Failed to insert data into database:" << query.lastError().text();
        } else {
            qDebug() << "Data inserted successfully.";
        }

        qDebug() << "---> step6";

        db.close();

        qDebug() << "---> step7";

        m_hasBarcode = false;
        m_hasWeight  = false;
    }
}


