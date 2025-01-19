#include "SettingsMenu.h"
#include "screen.h"
#include "RotaryEncoderHandler.h"

extern RotaryEncoderHandler encoderHandler;

int searchSpeed = 50; // Default value
int attackSpeed = 50; // Default value

void setupSettingsMenu(MenuSystem& menuSystem) {
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
      size_t currentOption = 0; // Track the currently selected submenu

      while (true) {
        // Render the Speed Settings Page
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Speed Settings:");

        // Render Search Speed
        display.setCursor(0, 10);
        if (currentOption == 0) display.print("> ");
        else display.print("  ");
        display.print("Search Speed: ");
        display.print("     "); // Ensure space for value
        display.setCursor(90, 10);
        display.print(searchSpeed);
        display.print("%");

        // Render Attack Speed
        display.setCursor(0, 20);
        if (currentOption == 1) display.print("> ");
        else display.print("  ");
        display.print("Attack Speed: ");
        display.print("     "); // Ensure space for value
        display.setCursor(90, 20);
        display.print(attackSpeed);
        display.print("%");

        // Render Instructions
        display.setCursor(0, 40);
        display.println("Rotate to adjust");
        display.setCursor(0, 50);
        display.println("Press to confirm");
        display.display();

        // Update rotary encoder
        encoderHandler.update();
        int rotation = encoderHandler.getRotation();

        // Navigate options
        if (rotation != 0) {
          currentOption = (currentOption + rotation + 2) % 2;
        }

        // Adjust values when the button is pressed
        if (encoderHandler.isButtonPressed()) {
          encoderHandler.resetButtonState();

          // Reference the selected value
          int& selectedSpeed = (currentOption == 0) ? searchSpeed : attackSpeed;

          // Allow adjustment
          while (true) {
            encoderHandler.update();
            int adjustment = encoderHandler.getRotation();

            // Highlight the selected option
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("Speed Settings:");

            display.setCursor(0, 10);
            if (currentOption == 0) {
              display.setTextColor(BLACK, WHITE); // Highlight Search Speed
              display.print("> Search Speed: ");
              display.print(searchSpeed);
              display.print("%");
              display.setTextColor(WHITE, BLACK); // Reset color
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
              display.setTextColor(WHITE, BLACK); // Reset color
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

            if (adjustment != 0) {
              selectedSpeed = constrain(selectedSpeed + adjustment, 0, 100);
            }

            if (encoderHandler.isButtonPressed()) {
              encoderHandler.resetButtonState();
              break; // Exit adjustment loop
            }
          }
        }

        // Exit menu on back button press
        if (digitalRead(cleanButtonPin) == LOW) {
          delay(250); // Debounce delay
          break; // Exit Speed Settings
        }
      }
    }),
    MenuItem("Sensors", []() {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Sensor Settings...");
      display.println("All sensors active."); // Placeholder for sensor info
      display.display();
      delay(1000);
    })
  }
                         ));
}
