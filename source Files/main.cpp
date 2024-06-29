#include <QCoreApplication>

#include "TcpServer.hpp"
#include "TrafficLightController.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto *trafficLightController = new TrafficLightController();

    trafficLightController->GreenLight();

    QTimer::singleShot(1000, trafficLightController, SLOT(YellowLight()));

    QTimer::singleShot(2000, trafficLightController, SLOT(RedLight()));


//    ITcpServer  *server = new TcpServer();

    return a.exec();
}
