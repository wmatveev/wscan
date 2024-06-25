//
// Created by wmatveev on 24.06.2024.
//

#ifndef WSCAN_SCANNERCONTROLLER_HPP
#define WSCAN_SCANNERCONTROLLER_HPP

#include <QObject>
#include <QSerialPort>
#include <QTextStream>
#include <QDebug>

class ScannerController : public QObject
{
    Q_OBJECT

    public:
        explicit ScannerController(QObject *parent = nullptr);
        ~ScannerController();

        QByteArray GetBarcode();

    private:
        bool SetupSerialPorts(const QVector<QString>& portNames, int baudRate);
        QByteArray ReadFromPort(int index);
        QVector<QByteArray> ReadFromAllPorts();

    private:
        QVector<QSerialPort*> m_ports;
};


#endif //WSCAN_SCANNERCONTROLLER_HPP
