//
// Created by wmatveev on 24.06.2024.
//

#include "ScannerController.hpp"


ScannerController::ScannerController(QObject *parent)
        : QObject(parent),
          m_http{new HttpController}
{
}

ScannerController::~ScannerController()
{
    delete m_http;
}

void ScannerController::ActivateScannerRelay()
{
    qDebug() << "Relay activated";
    m_http->SendSignalToDevice(url+cmdActivateScanner);
}

void ScannerController::DeactivateScannerRelay()
{
    qDebug() << "Relay deactivated";
    m_http->SendSignalToDevice(url+cmdDeactivateScanner);
}

