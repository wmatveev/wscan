//
// Created by wmatveev on 24.06.2024.
//

#ifndef WSCAN_LASERCONTROLLER_HPP
#define WSCAN_LASERCONTROLLER_HPP

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "ScannerController.hpp"
#include "HttpController.hpp"
#include "PortsController.hpp"
#include "ScaleController.hpp"
#include "TrafficLightController.hpp"

class LaserController : public QObject
{
    Q_OBJECT

    public:
        explicit LaserController(QObject *parent = nullptr);

    public slots:
        void onLaserTriggered(unsigned char);
        void onLaserReleased(unsigned char);
        void onGetBarcode(const QByteArray &data);
        void onGetWeight(const float &weight);

    public:
        void test();

    private:
        void TryInsertDataToDB();

    private:
        bool m_hasBarcode = false;
        bool m_hasWeight  = false;
        QByteArray m_barcodeData;
        float m_weightData = 0.0f;

        QTimer *m_timer = nullptr;
        ScannerController *m_scanner = nullptr;
        PortsController *m_portsController = nullptr;
        ScaleController *m_scaleController = nullptr;
        TrafficLightController *m_trafficlightController = nullptr;
};


#endif //WSCAN_LASERCONTROLLER_HPP
