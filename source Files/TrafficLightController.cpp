//
// Created by wmatveev on 29.06.2024.
//

#include "TrafficLightController.hpp"

TrafficLightController::TrafficLightController(QObject *parent)
        : QObject(parent),
          m_http{new HttpController}
{
}

TrafficLightController::~TrafficLightController()
{
    delete m_http;
}

void TrafficLightController::GreenLight()
{
    m_http->SendSignalToDevice(url + cmdToGreenLight);
}

void TrafficLightController::YellowLight()
{
    m_http->SendSignalToDevice(url + cmdToYellowLight);
}

void TrafficLightController::RedLight()
{
   m_http->SendSignalToDevice(url + cmdToRedLight);
}

