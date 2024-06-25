#include <QCoreApplication>

#include "TcpServer.hpp"
#include "ScannerController.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ScannerController *scanner = new ScannerController;
    ITcpServer  *server = new TcpServer(scanner);

    return a.exec();
}
