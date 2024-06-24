//
// Created by wmatveev on 24.06.2024.
//

#ifndef WSCAN_LASERSENSOR_HPP
#define WSCAN_LASERSENSOR_HPP

#include <QObject>
#include <QTimer>

class LaserSensor : public QObject
{
    Q_OBJECT

    public:
        explicit LaserSensor(QObject *parent = nullptr);

    public slots:
        void onLaserTriggered(unsigned char);
        void onLaserReleased(unsigned char);

    private:
        QTimer *m_timer = nullptr;
};


#endif //WSCAN_LASERSENSOR_HPP
