#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H
#include "structures/sensor_config.h"

// === PUBLIC ===
// Functions that should be used externally from this Header

// Initializez motor library
void setupStates();

void runStateManagerTick(DataHolder sensorDataHolder);

// === INTERNAL ===
// Available for use outside CPP, but shouldn't be used. 


#endif