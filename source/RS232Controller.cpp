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

    for (const QChar& c : input) {
        // Преобразуем каждый символ в его бинарное представление
        QString binaryChar = QString("%1").arg(c.unicode(), 8, 2, QLatin1Char('0'));
        // Преобразуем каждый бит в байт и добавляем в массив байтов
        for (int i = 0; i < binaryChar.size(); ++i) {
            binaryData.append(static_cast<char>(binaryChar.at(i).unicode()));
        }
    }
    return binaryData;
}

void RS232Controller::SendBarcodeToRS232(const QString& barcode)
{
    QString prefix = QString(QChar(0x02));  // Префикс (ASCII 0x02)
    QString suffix = QString(QChar(0x03));  // Суффикс (ASCII 0x03)
    QString fullBarcode = prefix + barcode + suffix;

    QByteArray binaryBarcode = ConvertToBinary(fullBarcode);

    m_http->SendSignalToDevice(url + cmdSendBarcodeToRS232 + binaryBarcode);
}
