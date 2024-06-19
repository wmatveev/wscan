#include "ScanStateMachine.hpp"

ScanStateMachine::ScanStateMachine(QObject *parent)
    : QObject{parent},
      idleState{new QState()},
      sensorTriggeredState{new QState()},
      processingState{new QState()},
      saveDataState{new QState()},
      greenLightState{new QState()}
{
    m_stateMachine.setInitialState(idleState);
}
