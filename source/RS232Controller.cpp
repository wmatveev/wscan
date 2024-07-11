//
// Created by wmatveev on 02.07.2024.
//

#include "RS232Controller.hpp"

RS232Controller::RS232Controller(QObject *parent)
        : QObject(parent),
          m_http{new HttpController}
{

}

QByteArray RS232Controller::ConvertToBinary(const QString& input)
{
    QString prefix = QString(QChar(0x237A)); // Unicode for ˺
    QString suffix = QString(QChar(0x237A)); // Unicode for ˪
    QString fullBarcode = prefix + input + suffix;

    QByteArray binaryData = fullBarcode.toUtf8();
    return binaryData;
}

void RS232Controller::SendBarcodeToRS232(const QString& barcode)
{
    QByteArray binaryBarcode = ConvertToBinary(barcode);

    m_http->SendSignalToDevice(url + cmdSendBarcodeToRS232 + binaryBarcode);
//    m_http->SendBinaryDataToDevice(url + cmdSendBarcodeToRS232, binaryBarcode);
}
