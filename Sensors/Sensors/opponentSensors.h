#ifndef OPPONENTSENSORS_H
#define OPPONENTSENSORS_H

#include <Arduino.h>
#include "sensor_config.h"

// === PUBLIC ===
// Functions that should be used externally from this Header

// Acquires raw opponent sensor data and preprocesses it
OpponentPositionResult aquireOpponentSensorData(OpponentSensorConfig opponentSensorConfig);

// === INTERNAL ===
// Available for use outside CPP, but shouldn't be used directly

// Collects the raw sensor data from the opponent sensors
RawOpponentSensorData collectOpponentSensorData(OpponentSensorConfig opponentSensorConfig);

// Does initial processing of the raw opponent sensor data
OpponentPositionResult preprocessRawOpponentSensorData(RawOpponentSensorData rawData);

#endif // OPPONENTSENSORS_H
