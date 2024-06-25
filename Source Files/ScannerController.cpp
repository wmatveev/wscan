//
// Created by wmatveev on 24.06.2024.
//

#include "ScannerController.hpp"


ScannerController::ScannerController(QObject *parent)
        : QObject(parent),
          m_hcontroller{new HttpController}
{
}

ScannerController::~ScannerController()
{
    delete m_hcontroller;
}





//QByteArray ScannerController::GetBarcode()
//{
//    m_hcontroller->ActivateScannerRelay(QString("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd="));
//
//    QVector<QByteArray> dataFromAllPorts;
//    dataFromAllPorts = ReadFromAllPorts();
//
//    for (const QByteArray &data : dataFromAllPorts)
//    {
//        if (!data.isEmpty()) {
//            m_hcontroller->DeactivateScannerRelay(QString("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd="));
//
//            return data;
//        }
//    }
//
//    m_hcontroller->DeactivateScannerRelay(QString("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd="));
//
//    return {};
//}
