#include <Arduino.h>
#include "menuSystem.h"
#include "RotaryEncoderHandler.h"
#include "screen.h"
#include "SettingsMenu.h"
#include "TestMenu.h"
#include "DebugMenu.h"
#include "StrategiesMenu.h"
#include "EEPROMHelper.h" // Include the EEPROM helper
#include "sensorMenu.h"

// Global Instances
RotaryEncoderHandler encoderHandler(clkPin, dtPin, swPin, 500);
MenuSystem menuSystem(encoderHandler, cleanButtonPin, 200);


SensorConfig sensorConfig; // Global SensorConfig

//int searchSpeed ; // Default value
//int attackSpeed; // Default value

void setup() {
  Serial.begin(115200);
  pinMode(cleanButtonPin, INPUT_PULLUP);


  // Load configurations from EEPROM
  loadSpeedFromEEPROM(searchSpeed, attackSpeed); // Load speed settings
  //loadSensorConfigFromEEPROM(sensorConfig);     // Load sensor configurations
  setupScreen();

  // Setup Settings Menu (including Sensors)
  setupSettingsMenu(menuSystem, sensorConfig);
  setupTestMenu(menuSystem);
  setupDebugMenu(menuSystem);
  setupStrategiesMenu(menuSystem);

  menuSystem.displayMenu();
}

void loop() {

  menuSystem.updateMenu();

  delay(50); // Pause for observation



}
