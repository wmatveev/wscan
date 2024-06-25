//
// Created by wmatveev on 16.06.2024.
//

#include "TcpServer.hpp"


/**
 * @brief TcpServer constructor
 * @param Parent
 */
TcpServer::TcpServer(ScannerController *scanner, QObject *parent)
        : QObject{parent},
          m_server{new QTcpServer(this)},
          m_laser{new LaserController(scanner, this)}
{
    connect(this, &TcpServer::sendInfo, this, &TcpServer::ShowInfo);

    if (!m_server->listen(QHostAddress::Any, 3030))
    {
        emit sendInfo( QString("The server did not start. Error: %1").arg(m_server->errorString()) );
        qDebug() << "The m_server did not start. Error: " << m_server->errorString();
    }
    else
    {
        emit sendInfo(QString("The server is running. Listening on the port %1").arg(m_server->serverPort()));
        connect(m_server, &QTcpServer::newConnection, this, &TcpServer::AcceptNewConnection);
    }

    connect(this, &TcpServer::laserTriggered, m_laser, &LaserController::onLaserTriggered);
    connect(this, &TcpServer::laserReleased,  m_laser, &LaserController::onLaserReleased);
}

/**
 * @brief Accept a connection from a new client and configure
 *        handlers for data reception and disconnection
 * @return Error code. If it's 0, everything's fine
 */
int TcpServer::AcceptNewConnection()
{
    m_socket = m_server->nextPendingConnection();

    if (m_socket != nullptr)
    {
        connect(m_socket, &QTcpSocket::readyRead,    this, &TcpServer::AcceptDataFromClient);
        connect(m_socket, &QTcpSocket::disconnected, this, &TcpServer::HandleClientDisconnection);

        emit sendInfo(QString("New connection from %1").arg(m_socket->peerAddress().toString()));

        return 0;
    }

    return -1;
}

/**
 * @brief Accept the data from client
 * @return Error code. If it's 0, everything's fine
 */
int TcpServer::AcceptDataFromClient()
{
    unsigned char data = 0xFF;

    QDataStream stream{m_socket};

    stream >> data;

    emit sendInfo( QString("------------------------------"));
    emit sendInfo( QString("Received the signal: %1").arg(static_cast<char>(data)) );

    if (data == '0') {
        emit laserTriggered(data);
    }
    else if (data == '1') {
        emit laserReleased(data);
    }

    return 0;
}

int TcpServer::HandleClientDisconnection()
{
    return 0;
}

void TcpServer::ShowInfo(QString s)
{
    qDebug() << s;
}
