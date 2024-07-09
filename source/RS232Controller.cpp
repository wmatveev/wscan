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
    QByteArray binaryData;

    for (const QChar& c : input)
    {
        QString binaryChar = QString("%1").arg(c.unicode(), 8, 2, QLatin1Char('0'));

        for (int i = 0; i < binaryChar.size(); ++i) {
            binaryData.append(static_cast<char>(binaryChar.at(i).unicode()));
        }
    }
    return binaryData;
}

void RS232Controller::SendBarcodeToRS232(const QString& barcode)
{
//    QString prefix = QString(QChar(0x02));  // Префикс (ASCII 0x02)
//    QString suffix = QString(QChar(0x03));  // Суффикс (ASCII 0x03)
//    QString fullBarcode = prefix + barcode + suffix;
//
//    QByteArray binaryBarcode = ConvertToBinary(fullBarcode);

    QString testBinaryData = "0000001000110100001110010011100000110100001100000011001000000011"; // Пример корректных данных
    QByteArray binaryData = QByteArray::fromHex(testBinaryData.toLatin1());

    qDebug() << "Test Binary Data:" << binaryData;

    m_http->SendBinaryDataToDevice(url + cmdSendBarcodeToRS232, binaryData);
}
