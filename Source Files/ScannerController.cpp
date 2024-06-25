//
// Created by wmatveev on 24.06.2024.
//

#include "ScannerController.hpp"


ScannerController::ScannerController(QObject *parent)
        : QObject(parent),
          m_hcontroller{new HttpController}
{
    QVector<QString> portNames = {
        "/dev/ttyACM0",
        "/dev/ttyACM1",
        "/dev/ttyACM2",
        "/dev/ttyACM3",
        "/dev/ttyACM4",
        "/dev/ttyACM5"
    };

    SetupSerialPorts(portNames, 9000);
}

ScannerController::~ScannerController()
{
    delete m_hcontroller;

    for (QSerialPort* port : m_ports) {
        if (port->isOpen()) {
            port->close();
        }
        delete port;
    }
}

bool ScannerController::SetupSerialPorts(const QVector<QString>& portNames, int baudRate)
{
    for (const QString &portName : portNames)
    {
        QSerialPort *port = new QSerialPort(portName, this);

        port->setBaudRate(baudRate);
        port->setDataBits(QSerialPort::Data8);
        port->setParity(QSerialPort::NoParity);
        port->setStopBits(QSerialPort::OneStop);
        port->setFlowControl(QSerialPort::NoFlowControl);

        if (!port->open(QIODevice::ReadOnly))
        {
            qDebug() << "Failed to open port" << portName << ":" << port->errorString();
            delete port;

            return false;
        }

        qDebug() << "Port was opened: " << portName;

        m_ports.append(port);
    }

    return true;
}

QByteArray ScannerController::ReadFromPort(int index)
{
    if (index < 0 || index >= m_ports.size()) {
        return {};
    }

    QSerialPort *port = m_ports.at(index);
    if (!port->isOpen()) {
        return {};
    }

    QByteArray data = port->readAll();

    qDebug() << data;

    return data;
}

QVector<QByteArray> ScannerController::ReadFromAllPorts()
{
    QVector<QByteArray> allData;

    for (int i = 0; i < m_ports.size(); ++i) {
        allData.append(ReadFromPort(i));
    }

    return allData;
}

QByteArray ScannerController::GetBarcode()
{
    m_hcontroller->ActivateScannerRelay(QString("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd="));

    QVector<QByteArray> dataFromAllPorts;
    dataFromAllPorts = ReadFromAllPorts();

    for (const QByteArray &data : dataFromAllPorts)
    {
        if (!data.isEmpty()) {
            m_hcontroller->DeactivateScannerRelay(QString("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd="));

            return data;
        }
    }

    m_hcontroller->DeactivateScannerRelay(QString("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd="));

    return {};
}
