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

        QString ReadFromPort(int index);
        QVector<QString> ReadFromAllPorts();


    private:
        bool SetupSerialPorts(const QVector<QString>& portNames, int baudRate);

    private:
        QVector<QSerialPort*> m_ports;
};


#endif //WSCAN_SCANNERCONTROLLER_HPP
