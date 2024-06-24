#include <QCoreApplication>

#include "TcpServer.hpp"
#include "ScannerController.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ScannerController *scanners = new ScannerController;
    ITcpServer  *server = new TcpServer;

    return a.exec();
}
