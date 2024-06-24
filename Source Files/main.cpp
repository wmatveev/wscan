#include <QCoreApplication>

#include "TcpServer.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ITcpServer  *server = new TcpServer;

    return a.exec();
}
