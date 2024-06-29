//
// Created by wmatveev on 25.06.2024.
//

#ifndef WSCAN_PORTSCONTROLLER_HPP
#define WSCAN_PORTSCONTROLLER_HPP

#include <QThread>
#include <QByteArray>
#include <QSerialPort>
#include <QDebug>



class PortsController : public QThread
{
    Q_OBJECT

    public:
        explicit PortsController(QObject *parent = nullptr);
        ~PortsController() override;

        void run() override;
        void stop();

    signals:
        void dataReadyForRead(const QByteArray &data);

    public slots:
        void stopReading();

    private:
        bool running;
        QVector<QSerialPort*> m_ports;

    private:
        bool SetupSerialPorts(const QVector<QString>& portNames, int baudRate);
        QByteArray ReadFromPort(int index);
        QVector<QByteArray> ReadFromAllPorts();
        QByteArray GetBarcode();

};


#endif //WSCAN_PORTSCONTROLLER_HPP
