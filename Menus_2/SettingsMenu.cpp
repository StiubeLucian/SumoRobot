#include "SettingsMenu.h"
#include "screen.h"
#include "RotaryEncoderHandler.h"
#include "SensorMenu.h" // Include SensorMenu for integration
#include "EEPROMHelper.h"



extern RotaryEncoderHandler encoderHandler;

// Default values for speed settings


void setupSettingsMenu(MenuSystem& menuSystem, SensorConfig& sensorConfig) {
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
    size_t currentOption = 0; // Track the currently selected option

    while (true) {
        // Render the Speed Settings Page
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Speed Settings:");

        // Render Search Speed with proper highlighting
        display.setCursor(0, 10);
        if (currentOption == 0) {
            display.setTextColor(BLACK, WHITE); // Highlight Search Speed
            display.print("> Search Speed: ");
            display.print(searchSpeed);
            display.print("%");
            display.setTextColor(WHITE, BLACK); // Reset text color
        } else {
            display.print("  Search Speed: ");
            display.print(searchSpeed);
            display.print("%");
        }

        // Render Attack Speed with proper highlighting
        display.setCursor(0, 20);
        if (currentOption == 1) {
            display.setTextColor(BLACK, WHITE); // Highlight Attack Speed
            display.print("> Attack Speed: ");
            display.print(attackSpeed);
            display.print("%");
            display.setTextColor(WHITE, BLACK); // Reset text color
        } else {
            display.print("  Attack Speed: ");
            display.print(attackSpeed);
            display.print("%");
        }

        // Render Instructions
        display.setCursor(0, 40);
        display.println("Rotate to navigate");
        display.setCursor(0, 50);
        display.println("Press to adjust");
        display.display();

        // Update rotary encoder
        encoderHandler.update();
        int rotation = encoderHandler.getRotation();

        // Navigate options
        if (rotation > 0) {
            currentOption = (currentOption + 1) % 2; // Move to the next option
        } else if (rotation < 0) {
            currentOption = (currentOption + 2 - 1) % 2; // Move to the previous option
        }

        // Adjust the selected speed only after button press
        if (encoderHandler.isButtonPressed()) {
            encoderHandler.resetButtonState();

            // Reference the selected speed variable
            int& selectedSpeed = (currentOption == 0) ? searchSpeed : attackSpeed;

            // Update speed value based on encoder rotation
            while (true) {
                encoderHandler.update();
                int adjustment = encoderHandler.getRotation();

                if (adjustment != 0) {
                    selectedSpeed = constrain(selectedSpeed + adjustment, 0, 100); // Adjust within range
                }

                // Re-render the same screen with updated value
                display.clearDisplay();
                display.setCursor(0, 0);
                display.println("Speed Settings:");

                display.setCursor(0, 10);
                if (currentOption == 0) {
                    display.setTextColor(BLACK, WHITE); // Highlight Search Speed
                    display.print("> Search Speed: ");
                    display.print(searchSpeed);
                    display.print("%");
                    display.setTextColor(WHITE, BLACK);
                } else {
                    display.print("  Search Speed: ");
                    display.print(searchSpeed);
                    display.print("%");
                }

                display.setCursor(0, 20);
                if (currentOption == 1) {
                    display.setTextColor(BLACK, WHITE); // Highlight Attack Speed
                    display.print("> Attack Speed: ");
                    display.print(attackSpeed);
                    display.print("%");
                    display.setTextColor(WHITE, BLACK);
                } else {
                    display.print("  Attack Speed: ");
                    display.print(attackSpeed);
                    display.print("%");
                }

                display.setCursor(0, 40);
                display.println("Rotate to adjust");
                display.setCursor(0, 50);
                display.println("Press to confirm");
                display.display();

                // Save and exit adjustment loop
                if (encoderHandler.isButtonPressed()) {
                    encoderHandler.resetButtonState();
                    saveSpeedToEEPROM(searchSpeed, attackSpeed); // Save to EEPROM
                    break;
                }

                // Exit adjustment loop on back button press
                if (digitalRead(cleanButtonPin) == LOW) {
                    delay(250); // Debounce
                    break;
                }
            }
        }

        // Exit menu on back button press
        if (digitalRead(cleanButtonPin) == LOW) {
            delay(250); // Debounce
            break;
        }
    }
}),


    MenuItem("Sensors", nullptr, {
      MenuItem("Opponent Sensors", [&]() {
        setupOpponentSensorsMenu(sensorConfig); // Navigate to Opponent Sensors
       // saveSensorConfigToEEPROM(sensorConfig); // Save updated config to EEPROM
      }),
      MenuItem("Line Sensors", [&]() {
        setupLineSensorsMenu(sensorConfig); // Navigate to Line Sensors
       // saveSensorConfigToEEPROM(sensorConfig); // Save updated config to EEPROM
      })
    })
  }));
}
