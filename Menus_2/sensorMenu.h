#ifndef SENSOR_MENU_H
#define SENSOR_MENU_H

#include "menuSystem.h"
#include "sensor_config.h"

// Function declarations
void setupSensorsMenu(MenuSystem& menuSystem, SensorConfig& sensorConfig);
void setupOpponentSensorsMenu(SensorConfig& sensorConfig);
void setupLineSensorsMenu(SensorConfig& sensorConfig);

#endif // SENSOR_MENU_H
