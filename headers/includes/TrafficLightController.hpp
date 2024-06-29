//
// Created by wmatveev on 29.06.2024.
//

#ifndef WSCAN_TRAFFICLIGHTCONTROLLER_HPP
#define WSCAN_TRAFFICLIGHTCONTROLLER_HPP

#include <QObject>
#include "HttpController.hpp"


class TrafficLightController : public QObject
{
    Q_OBJECT

    public:
        explicit TrafficLightController(QObject *parent = nullptr);
        ~TrafficLightController() override;


    public:
        void TurnOffAllTheLights();
        void GreenLight();
        void YellowLight();
        void RedLight();
        void BlueLight();

    private:
        HttpController *m_http = nullptr;
        QString cmdToGreenLight   = "WR,1,1";
        QString cmdToYellowLight  = "WR,2,1";
        QString cmdToRedLight     = "WR,3,1";
        QString cmdToBlueLight    = "WR,4,1";

        QString cmdTurnOffGreenLight   = "WR,1,0";
        QString cmdTurnOffYellowLight  = "WR,2,0";
        QString cmdTurnOffRedLight     = "WR,3,0";
        QString cmdTurnOffBlueLight    = "WR,4,0";

        QString url = "http://192.168.45.195/cmd.cgi?psw=Laurent&cmd=";
};


#endif //WSCAN_TRAFFICLIGHTCONTROLLER_HPP
