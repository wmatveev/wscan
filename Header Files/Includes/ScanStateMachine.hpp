#ifndef SCANSTATEMACHINE_H
#define SCANSTATEMACHINE_H

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QDebug>
#include <QTimer>

class ScanStateMachine : public QObject
{
    Q_OBJECT

    public:
        explicit ScanStateMachine(QObject *parent = nullptr);

    private:
        QState *idleState = nullptr;
        QState *sensorTriggeredState = nullptr;
        QState *processingState = nullptr;
        QState *saveDataState = nullptr;
        QState *greenLightState = nullptr;


    signals:

    private:
        QStateMachine m_stateMachine;
        QTimer m_timer;

};

#endif // SCANSTATEMACHINE_H
