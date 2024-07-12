#include <QCoreApplication>
#include "TcpServer.hpp"

#include "TrafficLightController.hpp"
#include "PortPolling.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    ITcpServer  *server = new TcpServer();

    PortPolling *portPolling = new PortPolling();

    portPolling->PollFirstPort();


    return a.exec();
}
