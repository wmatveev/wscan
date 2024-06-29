#include <QCoreApplication>

#include "TcpServer.hpp"
#include "ScannerController.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ITcpServer  *server = new TcpServer();

    return a.exec();
}
