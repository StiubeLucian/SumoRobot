#include "EEPROMHelper.h"

// Save speed settings to EEPROM
void saveSpeedToEEPROM(int searchSpeed, int attackSpeed) {
  EEPROM.put(EEPROM_SEARCH_SPEED_ADDR, searchSpeed); // Store search speed
  EEPROM.put(EEPROM_ATTACK_SPEED_ADDR, attackSpeed); // Store attack speed
}

// Load speed settings from EEPROM
void loadSpeedFromEEPROM(int& searchSpeed, int& attackSpeed) {
  EEPROM.get(EEPROM_SEARCH_SPEED_ADDR, searchSpeed); // Retrieve search speed
  EEPROM.get(EEPROM_ATTACK_SPEED_ADDR, attackSpeed); // Retrieve attack speed

  // Ensure loaded values are valid (add validation if necessary)
  if (searchSpeed < 0 || searchSpeed > 100) searchSpeed = 50;
  if (attackSpeed < 0 || attackSpeed > 100) attackSpeed = 50;
}

// Save sensor configuration to EEPROM
void saveSensorConfigToEEPROM(const SensorConfig& sensorConfig) {
  EEPROM.put(EEPROM_SENSOR_CONFIG_ADDR, sensorConfig); // Store the entire SensorConfig structure
}

// Load sensor configuration from EEPROM
void loadSensorConfigFromEEPROM(SensorConfig& sensorConfig) {
  EEPROM.get(EEPROM_SENSOR_CONFIG_ADDR, sensorConfig); // Retrieve the entire SensorConfig structure

  // Validate sensor configuration (optional)
  if (!sensorConfig.opponentSensorConfig.useOpponentSensors) {
    sensorConfig.opponentSensorConfig.useOpponentSensors = true;
  }
  if (!sensorConfig.lineSensorConfig.useLineSensors) {
    sensorConfig.lineSensorConfig.useLineSensors = true;
  }
}
