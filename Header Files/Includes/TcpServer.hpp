//
// Created by wmatveev on 16.06.2024.
//

#ifndef WSCAN_TCPSERVER_HPP
#define WSCAN_TCPSERVER_HPP

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "ITcpServer.hpp"
#include "ScanStateMachine.hpp"

class TcpServer : public QObject, public ITcpServer
{
    Q_OBJECT

    public:
        explicit TcpServer(QObject *parent = nullptr);

    private:
        QTcpServer* m_server = nullptr;
        QTcpSocket* m_socket = nullptr;
        ScanStateMachine *m_stateMachine;

    signals:
        void sendInfo(QString);
        void sensorTriggered();
        void sensorReleased();

    public slots:
        int AcceptNewConnection()  override;
        int AcceptDataFromClient() override;
        int HandleClientDisconnection() override;

        void ShowInfo(QString s);
};


#endif //WSCAN_TCPSERVER_HPP
