#ifndef LINESENSORS_H
#define LINESENSORS_H

#include <Arduino.h>
#include "sensor_config.h"

// === PUBLIC ===
// Functions that should be used externally from this Header

// Acquires raw line sensor data and preprocesses it
LinePositionResult aquireLineSensorData(LineSensorConfig lineSensorConfig);

// === INTERNAL ===
// Available for use outside CPP, but shouldn't be used directly

// Collects the raw sensor data from the line sensors
RawLineSensorData collectLineSensorData(LineSensorConfig lineSensorConfig);

// Does initial processing of the raw line sensor data
LinePositionResult preprocessRawLineSensorData(RawLineSensorData rawData);

#endif // LINESENSORS_H
