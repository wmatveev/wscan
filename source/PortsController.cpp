//
// Created by wmatveev on 25.06.2024.
//

#include "PortsController.hpp"

PortsController::PortsController(QObject *parent)
        : QThread(parent),
          running{false}
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

PortsController::~PortsController()
{
    for (QSerialPort* port : m_ports) {
        if (port->isOpen()) {
            port->close();
        }

        delete port;
    }

    stop();
}

bool PortsController::SetupSerialPorts(const QVector<QString>& portNames, int baudRate)
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

QByteArray PortsController::ReadFromPort(int index)
{
    if (index < 0 || index >= m_ports.size()) {
        return {};
    }

    QSerialPort *port = m_ports.at(index);
    if (!port->isOpen()) {
        return {};
    }

    QByteArray data = port->readAll();

    return data;
}

QVector<QByteArray> PortsController::ReadFromAllPorts()
{
    QVector<QByteArray> allData;

    for (int i = 0; i < m_ports.size(); ++i) {
        allData.append(ReadFromPort(i));
    }

    return allData;
}

QByteArray PortsController::GetBarcode()
{
    QVector<QByteArray> dataFromAllPorts;
    dataFromAllPorts = ReadFromAllPorts();

    for (QByteArray &data : dataFromAllPorts)
    {
        if (!data.isEmpty()) {
            data = data.trimmed();
            return data;
        }
    }

    return {};
}


void PortsController::run()
{
    running = true;

    while (running)
    {
        QByteArray data = GetBarcode();
        if (!data.isEmpty())
        {
            emit dataReadyForRead(data);
            running = false;
        }
        QThread::msleep(100);
    }
}

void PortsController::stop()
{
    running = false;
    wait();
}

void PortsController::stopReading()
{
    stop();
}
