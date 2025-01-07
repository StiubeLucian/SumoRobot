#ifndef STATES_MOVE_FORWARD_H
#define STATES_MOVE_FORWARD_H

#include <Arduino.h>
#include "../structures/sensor_config.h"
#include "../structures/state.h"
#include "debug_state.h"
#include "../motor_manager.h"

#define STATE_MOVE_FORWARD 1

int tick = 0;

bool stateMoveForwardRunTick(DataHolder sensorDataHolder) {
    if (tick > 10) {
        return true;
    }

    if (tick < 1) {
        setMotor(1, 127);
    }

    tick++;
    
    return false;
}

int stateMoveForwardGetNextState() {
    return STATE_DEBUG;
}

State stateMoveForward = {STATE_MOVE_FORWARD, stateMoveForwardRunTick, stateMoveForwardGetNextState};

#endif