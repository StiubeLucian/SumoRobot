#include "SettingsMenu.h"
#include "screen.h"
#include "RotaryEncoderHandler.h"
#include "SensorMenu.h" // Include SensorMenu for integration
#include "EEPROMHelper.h"

extern RotaryEncoderHandler encoderHandler;

// Default values for speed settings
//int searchSpeed = 50;
//int attackSpeed = 50;


void setupSettingsMenu(MenuSystem& menuSystem, SensorConfig& sensorConfig) {
  // Load initial speed settings from EEPROM
  loadSpeedFromEEPROM(searchSpeed, attackSpeed);

  menuSystem.addMenuItem(MenuItem(
                           "Settings",
                           nullptr,
  {
    MenuItem("Clean Wheels", []() {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Activating Clean Wheels...");
      display.display();
      delay(1000);
    }),
    MenuItem("Speed", []() {
      int currentOption = 0; // Start pointing at the first option
      bool inAdjustmentMode = false; // Adjustment mode disabled initially

      // Reset button states to avoid false triggers
      encoderHandler.resetButtonState();

      while (true) {
        // Selection menu logic (not in adjustment mode)
        if (!inAdjustmentMode) {
          display.clearDisplay();
          display.setCursor(0, 0);
          display.println("Speed Settings:");

          // Display "Search Speed"
          display.setCursor(0, 10);
          if (currentOption == 0) display.print("> ");
          else display.print("  ");
          display.print("Search Speed:");
          display.setCursor(90, 10);
          display.print(searchSpeed);
          display.print("%");

          // Display "Attack Speed"
          display.setCursor(0, 20);
          if (currentOption == 1) display.print("> ");
          else display.print("  ");
          display.print("Attack Speed:");
          display.setCursor(90, 20);
          display.print(attackSpeed);
          display.print("%");

          // Instructions
          display.setCursor(0, 40);
          display.println("Rotate to select");
          display.setCursor(0, 50);
          display.println("Press to adjust");
          display.display();

          // Handle rotary encoder input for scrolling
          encoderHandler.update();
          int rotation = encoderHandler.getRotation();
          if (rotation != 0) {
            currentOption = (currentOption + rotation + 2) % 2; // Scroll between options
          }

          // Handle button press to enter adjustment mode
          if (encoderHandler.isButtonPressed()) {
            encoderHandler.resetButtonState();
            inAdjustmentMode = true; // Enter adjustment mode
          }

          // Handle back button to exit the menu
          if (digitalRead(cleanButtonPin) == LOW) {
            delay(250);
            break; // Exit the speed menu
          }
        }

        // Adjustment mode
        if (inAdjustmentMode) {
          while (true) {
            encoderHandler.update();
            int adjustment = encoderHandler.getRotation();

            // Determine which speed to adjust
            int& selectedSpeed = (currentOption == 0) ? searchSpeed : attackSpeed;

            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("Adjust Speed:");

            // Highlight the currently selected option
            display.setCursor(0, 10);
            if (currentOption == 0) {
              display.setTextColor(BLACK, WHITE); // Inverted colors
              display.print("> Search Speed:");
              display.print(searchSpeed);
              display.print("%");
              display.setTextColor(WHITE, BLACK);
            } else {
              display.print("  Search Speed:");
              display.print(searchSpeed);
              display.print("%");
            }

            display.setCursor(0, 20);
            if (currentOption == 1) {
              display.setTextColor(BLACK, WHITE); // Inverted colors
              display.print("> Attack Speed:");
              display.print(attackSpeed);
              display.print("%");
              display.setTextColor(WHITE, BLACK);
            } else {
              display.print("  Attack Speed:");
              display.print(attackSpeed);
              display.print("%");
            }

            // Instructions
            display.setCursor(0, 40);
            display.println("Rotate to adjust");
            display.setCursor(0, 50);
            display.println("Press to confirm");
            display.display();

            // Adjust value
            if (adjustment != 0) {
              selectedSpeed = constrain(selectedSpeed + adjustment, 0, 100);
            }

            // Exit adjustment mode on button press and save to EEPROM
            if (encoderHandler.isButtonPressed()) {
              encoderHandler.resetButtonState();
              saveSpeedToEEPROM(searchSpeed, attackSpeed); // Save both speeds
              inAdjustmentMode = false; // Go back to selection mode
              break;
            }

            // Handle back button
            if (digitalRead(cleanButtonPin) == LOW) {
              delay(250);
              inAdjustmentMode = false;
              break; // Exit adjustment mode
            }
          }
        }
      }
    }),
    MenuItem("Sensors", nullptr, {
      MenuItem("Opponent Sensors", [&]() {
        setupOpponentSensorsMenu(sensorConfig); // Navigate to Opponent Sensors
      }),
      MenuItem("Line Sensors", [&]() {
        setupLineSensorsMenu(sensorConfig); // Navigate to Line Sensors
      })
    })
  }));
}
