#include "ScanStateMachine.hpp"
#include <QDebug>

ScanStateMachine::ScanStateMachine(QObject *parent)
        : QObject{parent},
          idleState{new QState()},
          sensorTriggeredState{new QState()},
          processingState{new QState()},
          saveDataState{new QState()},
          greenLightState{new QState()}
{
    setupStates();
    m_stateMachine.setInitialState(idleState);
    m_stateMachine.start();
}

void ScanStateMachine::setupStates()
{
    // Idle State
    connect(idleState, &QState::entered, this, []() {
        qDebug() << "IdleState: Waiting for sensor trigger...";
    });

    // Sensor Triggered State
    connect(sensorTriggeredState, &QState::entered, this, [this]() {
        qDebug() << "SensorTriggeredState: Sensor triggered, waiting for 3 seconds...";
        m_timer.start(3000);
    });
    connect(sensorTriggeredState, &QState::exited, this, [this]() {
        m_timer.stop();
    });

    // Processing State
    connect(processingState, &QState::entered, this, &ScanStateMachine::onProcessingDone);

    // Save Data State
    connect(saveDataState, &QState::entered, this, &ScanStateMachine::onDataSaved);

    // Green Light State
    connect(greenLightState, &QState::entered, this, [this]() {
        qDebug() << "GreenLightState: Switching traffic light to green...";
        sendRequest("WR,1,1"); // Example request
        QTimer::singleShot(2000, this, &ScanStateMachine::resetToIdle);
    });

    // Transitions
    idleState->addTransition(this, &ScanStateMachine::sensorTriggered, sensorTriggeredState);
    sensorTriggeredState->addTransition(this, &ScanStateMachine::sensorReleased, idleState);
    sensorTriggeredState->addTransition(&m_timer, &QTimer::timeout, processingState);
    processingState->addTransition(this, &ScanStateMachine::processingDone, saveDataState);
    saveDataState->addTransition(this, &ScanStateMachine::dataSaved, greenLightState);
    greenLightState->addTransition(this, &ScanStateMachine::resetToIdle, idleState);

    // Add states to state machine
    m_stateMachine.addState(idleState);
    m_stateMachine.addState(sensorTriggeredState);
    m_stateMachine.addState(processingState);
    m_stateMachine.addState(saveDataState);
    m_stateMachine.addState(greenLightState);
}

void ScanStateMachine::onSensorTriggered()
{
    emit sensorTriggered();
}

void ScanStateMachine::onSensorReleased()
{
    emit sensorReleased();
}

void ScanStateMachine::onProcessingDone()
{
    qDebug() << "ProcessingState: Processing barcode and weight...";
    QTimer::singleShot(1000, this, &ScanStateMachine::processingDone); // Simulate processing
}

void ScanStateMachine::onDataSaved()
{
    qDebug() << "SaveDataState: Saving data to the database...";
    QTimer::singleShot(500, this, &ScanStateMachine::dataSaved); // Simulate saving data
}

void ScanStateMachine::sendRequest(const QString &cmd)
{
    QNetworkRequest request(QUrl(QString("http://192.168.45.195/cmd.cgi?psw=Laurent&cmd=%1").arg(cmd)));
    m_manager.get(request);
}
