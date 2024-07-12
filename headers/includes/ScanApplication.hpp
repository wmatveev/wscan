//
// Created by wmatveev on 12.07.2024.
//

#ifndef WSCAN_SCANAPPLICATION_HPP
#define WSCAN_SCANAPPLICATION_HPP


#include <QObject>

class ScanApplication : public QObject
{
    Q_OBJECT

    public:
        explicit ScanApplication(QObject *parent = nullptr);

        void RunApplication();
};


#endif //WSCAN_SCANAPPLICATION_HPP
