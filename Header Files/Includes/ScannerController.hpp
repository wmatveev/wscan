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

    private:
        HttpController *m_hcontroller = nullptr;
};


#endif //WSCAN_SCANNERCONTROLLER_HPP
