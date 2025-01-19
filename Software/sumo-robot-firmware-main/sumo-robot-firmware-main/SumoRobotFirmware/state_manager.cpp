#include "state_manager.h"

#include <Arduino.h>
#include "structures/state.h"

#include "states/debug_state.h"
#include "states/move_forward_state.h"

State stateMap[50];
State currentState;

void setupStates() {
    // We add all states to list
    stateMap[STATE_DEBUG] = stateDebug;
    stateMap[STATE_MOVE_FORWARD] = stateMoveForward;

    // We set current state
    currentState = stateMap[STATE_MOVE_FORWARD];
}

void runStateManagerTick(DataHolder sensorDataHolder) {

    Serial.print("Current state is: ");
    Serial.println(currentState.id);

    // No complex transition logic here yet
    bool done = currentState.runTick(sensorDataHolder);

    if (done) {
        int nextStateIndex = currentState.getNextState();
        State nextState = stateMap[nextStateIndex];
        currentState = nextState;
    }
}