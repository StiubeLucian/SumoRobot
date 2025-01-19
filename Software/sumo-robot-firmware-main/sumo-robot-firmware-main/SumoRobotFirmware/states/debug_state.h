#ifndef STATES_DEBUG_H
#define STATES_DEBUG_H

#include <Arduino.h>
#include "../structures/sensor_config.h"
#include "../structures/state.h"

#define STATE_DEBUG 0

bool stateDebugRunTick(DataHolder sensorDataHolder) {
    Serial.println(sensorDataHolder.currentSensorData.hasData);
    return false;
}

int stateDebugGetNextState() {
    return STATE_DEBUG;
}

State stateDebug = {STATE_DEBUG, stateDebugRunTick, stateDebugGetNextState};

#endif