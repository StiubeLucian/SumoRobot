#ifndef OPPONENT_SENSORS_H
#define OPPONENT_SENSORS_H
#include <Arduino.h>
#include "structures/sensor_config.h"

// === PUBLIC ===
// Functions that should be used externally from this Header

// Aquires raw oponent sensor data nad preprocesses it
OpponentPositionResult aquireOpponentSensorData(OpponentSensorConfig opponentSensorConfig);


// === INTERNAL ===
// Available for use outside CPP, but shouldn't be used. 

// Collects the raw sensor data from the oponent sensor
RawOpponentSensorData collectOpponentSensorData(OpponentSensorConfig opponentSensorConfig);

// Does initial processing of the raw oponent sensor data
OpponentPositionResult preprocessRawOpponentSensorData(RawOpponentSensorData);

#endif
