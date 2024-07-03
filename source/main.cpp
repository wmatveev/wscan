#include <QCoreApplication>
#include "TcpServer.hpp"

#include "TrafficLightController.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    ITcpServer  *server = new TcpServer();

    int ms = 500;

    TrafficLightController *m_tl = new TrafficLightController;

    while (1)
    {
        m_tl->TurnOffAllTheLights();
        m_tl->BlueLight();
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        m_tl->TurnOffAllTheLights();
        m_tl->YellowLight();
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        m_tl->TurnOffAllTheLights();
        m_tl->GreenLight();
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        m_tl->TurnOffAllTheLights();
        m_tl->RedLight();
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    return a.exec();
}
