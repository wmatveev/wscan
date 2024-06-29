#include <QCoreApplication>

#include <thread>
#include <chrono>

#include "TcpServer.hpp"
#include "TrafficLightController.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto *trafficLightController = new TrafficLightController();

    for(int i=0; i<100 ;i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        trafficLightController->GreenLight();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        trafficLightController->YellowLight();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        trafficLightController->RedLight();
    }

//    ITcpServer  *server = new TcpServer();

    return a.exec();
}
