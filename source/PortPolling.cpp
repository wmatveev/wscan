//
// Created by wmatveev on 12.07.2024.
//

#include "PortPolling.hpp"

PortPolling::PortPolling(QObject *parent)
        : QObject(parent),
          m_http{new HttpController}
{

}

void PortPolling::PollFirstPort()
{
    QByteArray responseData;

    responseData = m_http->SendSignalToDevice(url + cmdPollFirstPort);

    qDebug() << "{Response Data}:" << responseData;
}
