//
// Created by wmatveev on 02.07.2024.
//

#include "RS232Controller.hpp"

RS232Controller::RS232Controller(QObject *parent)
        : QObject(parent),
          m_http{new HttpController}
{

}

void RS232Controller::SendBarcodeToRS232(const QString& barcode)
{
    m_http->SendSignalToDevice(url + cmdSendBarcodeToRS232 + barcode);
}
