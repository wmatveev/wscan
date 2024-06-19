#ifndef SCANSTATEMACHINE_H
#define SCANSTATEMACHINE_H

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QDebug>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>


class ScanStateMachine : public QObject
{
    Q_OBJECT

    public:
        explicit ScanStateMachine(QObject *parent = nullptr);

    signals:
        void sensorTriggered();
        void sensorReleased();
        void processingDone();
        void dataSaved();
        void resetToIdle();

    public slots:
        void onSensorTriggered();
        void onSensorReleased();
        void onProcessingDone();
        void onDataSaved();

    private:
        void setupStates();
        void sendRequest(const QString &cmd);

        QStateMachine m_stateMachine;
        QState *idleState;
        QState *sensorTriggeredState;
        QState *processingState;
        QState *saveDataState;
        QState *greenLightState;
        QTimer m_timer;
        QNetworkAccessManager m_manager;

};

#endif // SCANSTATEMACHINE_H
