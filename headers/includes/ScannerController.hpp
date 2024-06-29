//
// Created by wmatveev on 24.06.2024.
//

#ifndef WSCAN_SCANNERCONTROLLER_HPP
#define WSCAN_SCANNERCONTROLLER_HPP

#include <QObject>
#include <QSerialPort>
#include <QTextStream>
#include <QDebug>

#include "HttpController.hpp"

class ScannerController : public QObject
{
    Q_OBJECT

    public:
        explicit ScannerController(QObject *parent = nullptr);
        ~ScannerController() override;

        void ActivateScannerRelay();
        void DeactivateScannerRelay();

    private:
        HttpController *m_http = nullptr;
        QString cmdActivateScanner   = "REL,1,1";
        QString cmdDeactivateScanner = "REL,1,0";
        QString url = "http://192.168.45.195/cmd.cgi?psw=Laurent&cmd=";
};


#endif //WSCAN_SCANNERCONTROLLER_HPP
