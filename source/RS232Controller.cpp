//
// Created by wmatveev on 02.07.2024.
//

#include "RS232Controller.hpp"

RS232Controller::RS232Controller(QObject *parent)
        : QObject(parent),
          m_http{new HttpController}
{

}

QString RS232Controller::ConvertToBinary(const QString& input)
{
    QString binaryString;
    for (const QChar& c : input) {
        QString binaryChar = QString("%1").arg(c.unicode(), 8, 2, QLatin1Char('0'));
        binaryString.append(binaryChar);
//        binaryString.append("\n");
    }
    return binaryString;
}

void RS232Controller::SendBarcodeToRS232(const QString& barcode)
{
    QString prefix = QString(QChar(0x02));  // Префикс (ASCII 0x02)
    QString suffix = QString(QChar(0x03));  // Суффикс (ASCII 0x03)
    QString fullBarcode = prefix + barcode + suffix;

    QString binaryBarcode = ConvertToBinary(fullBarcode);

    qDebug() << "[Barcode}: " << barcode;
    qDebug() << "[Binary barcode}:" << binaryBarcode;

//    QStringList binaryLines = binaryBarcode.split("\n", QString::SkipEmptyParts);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)) && (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QStringList binaryLines = binaryBarcode.split("\n", QString::SkipEmptyParts);
#else
    QStringList binaryLines = binaryBarcode.split("\n", Qt::SkipEmptyParts);
#endif

    m_http->SendBinaryDataToDevice(url, cmdSendBarcodeToRS232 + binaryBarcode);
}
