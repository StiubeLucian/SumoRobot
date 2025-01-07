#include <Arduino.h>
#include "screen.h"
#include "menuSystem.h"
#include "RotaryEncoderHandler.h"
#include "Pins.h"
#include "TestMenu.h"
#include "DebugMenu.h"
#include "StrategiesMenu.h"
#include "SettingsMenu.h"

// Global Instances
RotaryEncoderHandler encoderHandler(clkPin, dtPin, swPin, 500);
MenuSystem menuSystem(encoderHandler, cleanButtonPin, 200);

void setup() {
  Serial.begin(115200);
  pinMode(cleanButtonPin, INPUT_PULLUP);

  setupScreen();

  // Setup individual menus
  setupSettingsMenu(menuSystem);
  setupTestMenu(menuSystem);
  setupDebugMenu(menuSystem);
  setupStrategiesMenu(menuSystem);


  // Set the back action for the menu system
  menuSystem.setBackAction([]() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Returning to Main Menu...");
    display.display();
    delay(1000);
  });

  menuSystem.displayMenu();
}

void loop() {
  menuSystem.updateMenu();
  delay(50);
}
