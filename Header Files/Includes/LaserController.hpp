//
// Created by wmatveev on 24.06.2024.
//

#ifndef WSCAN_LASERCONTROLLER_HPP
#define WSCAN_LASERCONTROLLER_HPP

#include <QObject>
#include <QTimer>
#include "ScannerController.hpp"

class LaserController : public QObject
{
    Q_OBJECT

    public:
        explicit LaserController(ScannerController *scanner, QObject *parent = nullptr);

    public slots:
        void onLaserTriggered(unsigned char);
        void onLaserReleased(unsigned char);

    private:
        QTimer *m_timer = nullptr;
        ScannerController *m_scanner = nullptr;
};


#endif //WSCAN_LASERCONTROLLER_HPP
