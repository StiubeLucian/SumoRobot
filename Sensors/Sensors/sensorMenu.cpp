#include "SensorMenu.h"
#include "screen.h"
#include "RotaryEncoderHandler.h"

extern RotaryEncoderHandler encoderHandler;

void setupSensorsMenu(MenuSystem& menuSystem, SensorConfig& sensorConfig) {
  menuSystem.addMenuItem(MenuItem(
                           "Sensors",
                           nullptr,
  {
    // Opponent Sensors Submenu
    MenuItem("Opponent Sensors", [&]() {
      size_t currentOption = 0;
      size_t scrollOffset = 0;
      const size_t maxVisibleItems = 8; // Maximum visible items on the screen

      while (true) {
        // Render the Opponent Sensors menu
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Opponent Sensors:");

        for (size_t i = 0; i < maxVisibleItems; i++) {
          size_t sensorIndex = scrollOffset + i;
          if (sensorIndex >= 11) break; // Stop if no more sensors to display

          display.setCursor(0, 10 + (i * 8));
          if (sensorIndex == currentOption) display.print("> ");
          else display.print("  ");
          display.print("Sensor ");
          display.print(sensorIndex + 1);
          display.print(": ");
          display.print(((&sensorConfig.opponentSensorConfig.useSensor1)[sensorIndex]) ? "ON" : "OFF");
        }

        display.display();

        // Update encoder
        encoderHandler.update();
        int rotation = encoderHandler.getRotation();

        // Navigate options
        if (rotation > 0) {
          if (currentOption < 10) currentOption++;
          if (currentOption >= scrollOffset + maxVisibleItems) {
            scrollOffset++;
          }
        } else if (rotation < 0) {
          if (currentOption > 0) currentOption--;
          if (currentOption < scrollOffset) {
            scrollOffset--;
          }
        }

        // Toggle sensor state on button press
        if (encoderHandler.isButtonPressed()) {
          encoderHandler.resetButtonState();
          bool& selectedSensor = (&sensorConfig.opponentSensorConfig.useSensor1)[currentOption];
          selectedSensor = !selectedSensor;
        }

        // Exit menu on back button press
        if (digitalRead(cleanButtonPin) == LOW) {
          delay(250); // Debounce
          break;
        }
      }
    }),

    // Line Sensors Submenu
    MenuItem("Line Sensors", [&]() {
      size_t currentOption = 0;

      while (true) {
        // Render the Line Sensors menu
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Line Sensors:");

        const char* lineSensorNames[] = {"Front Left", "Front Right", "Back Left", "Back Right"};
        for (size_t i = 0; i < 4; i++) {
          display.setCursor(0, 10 + (i * 8));
          if (i == currentOption) display.print("> ");
          else display.print("  ");
          display.print(lineSensorNames[i]);
          display.print(": ");
          display.print(((&sensorConfig.lineSensorConfig.useFrontLeft)[i]) ? "ON" : "OFF");
        }

        display.display();

        // Update encoder
        encoderHandler.update();
        int rotation = encoderHandler.getRotation();

        // Navigate options
        if (rotation != 0) {
          currentOption = (currentOption + rotation + 4) % 4;
        }

        // Toggle sensor state on button press
        if (encoderHandler.isButtonPressed()) {
          encoderHandler.resetButtonState();
          bool& selectedSensor = (&sensorConfig.lineSensorConfig.useFrontLeft)[currentOption];
          selectedSensor = !selectedSensor;
        }

        // Exit menu on back button press
        if (digitalRead(cleanButtonPin) == LOW) {
          delay(250); // Debounce
          break;
        }
      }
    })
  }));
}
