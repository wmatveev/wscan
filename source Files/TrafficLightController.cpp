//
// Created by wmatveev on 29.06.2024.
//

#include "TrafficLightController.hpp"

TrafficLightController::TrafficLightController(QObject *parent)
        : QObject(parent),
          m_http{new HttpController}
{
    TurnOffAllTheLights();
}

TrafficLightController::~TrafficLightController()
{
    delete m_http;
}

void TrafficLightController::TurnOffAllTheLights()
{
    m_http->SendSignalToDevice(url + cmdTurnOffGreenLight);
    m_http->SendSignalToDevice(url + cmdTurnOffYellowLight);
    m_http->SendSignalToDevice(url + cmdTurnOffRedLight);
    m_http->SendSignalToDevice(url + cmdTurnOffBlueLight);
}

void TrafficLightController::GreenLight()
{
    TurnOffAllTheLights();
    m_http->SendSignalToDevice(url + cmdToGreenLight);
}

void TrafficLightController::YellowLight()
{
    TurnOffAllTheLights();
    m_http->SendSignalToDevice(url + cmdToYellowLight);
}

void TrafficLightController::RedLight()
{
    TurnOffAllTheLights();
    m_http->SendSignalToDevice(url + cmdToRedLight);
}

void TrafficLightController::BlueLight()
{
    TurnOffAllTheLights();
    m_http->SendSignalToDevice(url + cmdToBlueLight);
}
