#include <QCoreApplication>
#include "TcpServer.hpp"

#include "ScanApplication.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ScanApplication app;
    app.RunApplication();


    return a.exec();
}
