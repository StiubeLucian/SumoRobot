#ifndef EEPROM_HELPER_H
#define EEPROM_HELPER_H

#include <EEPROM.h>
#include "sensor_config.h" // Include the SensorConfig definition

// EEPROM Addresses
#define EEPROM_SEARCH_SPEED_ADDR 0
#define EEPROM_ATTACK_SPEED_ADDR 1
#define EEPROM_SENSOR_CONFIG_ADDR 10 // Starting address for sensor configurations

// Function Declarations
void saveSpeedToEEPROM(int searchSpeed, int attackSpeed);
void loadSpeedFromEEPROM(int& searchSpeed, int& attackSpeed);

void saveSensorConfigToEEPROM(const SensorConfig& sensorConfig);
void loadSensorConfigFromEEPROM(SensorConfig& sensorConfig);

#endif // EEPROM_HELPER_H
