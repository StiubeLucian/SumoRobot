#ifndef LINE_SENSORS_H
#define LINE_SENSORS_H
#include <Arduino.h>
#include "structures/sensor_config.h"

// === PUBLIC ===
// Functions that shoudl be used externally from this Header

// Aquires raw line sensor data and preprocesses it
LinePositionResult aquireLineSensorData(LineSensorConfig LineSensorConfig);


// === INTERNAL ===
// Available for use outside CPP, but shouldn't be used. 

// Collects the raw sensor data from the oponent sensor
RawLineSensorData collectLineSensorData(LineSensorConfig LineSensorConfig);

// Does initial processing of the raw line sensor data
LinePositionResult preprocessRawLineSensorData(RawLineSensorData);

#endif
