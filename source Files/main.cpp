#include <QCoreApplication>
#include "TcpServer.hpp"

#include "LaserController.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    ITcpServer  *server = new TcpServer();

    LaserController laserController;
    laserController.test();

    return a.exec();
}
