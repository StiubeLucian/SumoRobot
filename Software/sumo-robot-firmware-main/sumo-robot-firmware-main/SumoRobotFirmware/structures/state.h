#ifndef STRUCTURES_STATE_H
#define STRUCTURES_STATE_H

#include "sensor_config.h"

typedef struct
{
    // Name of the state
    int id;

    // Takes DataHolder as parameter containing current and previous sensor reading
    // Returns true if state finished, false otherwise
    bool (*runTick)(DataHolder sensorDataHolder);

    // Returns next state to transition to
    int (*getNextState)();

} State;

#endif