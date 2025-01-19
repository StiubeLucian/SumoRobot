#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include "menuSystem.h"
#include "sensor_config.h"

// Declare speed settings with external linkage
extern int searchSpeed;
extern int attackSpeed;

// Function declaration for setting up Settings menu
void setupSettingsMenu(MenuSystem& menuSystem, SensorConfig& sensorConfig);

#endif // SETTINGS_MENU_H
