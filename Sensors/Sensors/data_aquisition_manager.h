#ifndef DATA_AQUISITION_MANAGER_H
#define DATA_AQUISITION_MANAGER_H
#include "sensor_config.h"

// === PUBLIC ===
// Functions that shoudl be used externally from this Header

// Aquires all sensor data based on configuration
SensorData aquireAllSensorData(SensorConfig sensorConfig);

// Prints to serial given SensorData
void printSensorDataToSerial(SensorData sensorData);

#endif
