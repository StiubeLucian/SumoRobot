#include <Arduino.h>
#include "menuSystem.h"
#include "sensorMenu.h"
#include "screen.h"
#include "RotaryEncoderHandler.h"
#include "Pins.h"

RotaryEncoderHandler encoderHandler(clkPin, dtPin, swPin, 500);
MenuSystem menuSystem(encoderHandler, cleanButtonPin, 200);
SensorConfig sensorConfig;


void setup() {
  Serial.begin(115200);
  setupScreen();
  setupSensorsMenu(menuSystem, sensorConfig);
}

void loop() {
  menuSystem.updateMenu();
  encoderHandler.update();
}
