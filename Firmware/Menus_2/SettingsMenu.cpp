#include "SettingsMenu.h"
#include "screen.h"
#include "RotaryEncoderHandler.h"
#include "SensorMenu.h" // Include SensorMenu for integration

extern RotaryEncoderHandler encoderHandler;

// Default values for speed settings
int searchSpeed = 50;
int attackSpeed = 50;

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
                size_t currentOption = 0;

                while (true) {
                    display.clearDisplay();
                    display.setCursor(0, 0);
                    display.println("Speed Settings:");

                    display.setCursor(0, 10);
                    if (currentOption == 0) display.print("> ");
                    else display.print("  ");
                    display.print("Search Speed: ");
                    display.setCursor(90, 10);
                    display.print(searchSpeed);
                    display.print("%");

                    display.setCursor(0, 20);
                    if (currentOption == 1) display.print("> ");
                    else display.print("  ");
                    display.print("Attack Speed: ");
                    display.setCursor(90, 20);
                    display.print(attackSpeed);
                    display.print("%");

                    display.setCursor(0, 40);
                    display.println("Rotate to adjust");
                    display.setCursor(0, 50);
                    display.println("Press to confirm");
                    display.display();

                    encoderHandler.update();
                    int rotation = encoderHandler.getRotation();
                    if (rotation != 0) {
                        currentOption = (currentOption + rotation + 2) % 2;
                    }

                    if (encoderHandler.isButtonPressed()) {
                        encoderHandler.resetButtonState();
                        int& selectedSpeed = (currentOption == 0) ? searchSpeed : attackSpeed;

                        while (true) {
                            encoderHandler.update();
                            int adjustment = encoderHandler.getRotation();

                            display.clearDisplay();
                            display.setCursor(0, 0);
                            display.println("Speed Settings:");

                            display.setCursor(0, 10);
                            if (currentOption == 0) {
                                display.setTextColor(BLACK, WHITE);
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
                                display.setTextColor(BLACK, WHITE);
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

                            if (adjustment != 0) {
                                selectedSpeed = constrain(selectedSpeed + adjustment, 0, 100);
                            }

                            if (encoderHandler.isButtonPressed()) {
                                encoderHandler.resetButtonState();
                                break;
                            }
                        }
                    }

                    if (digitalRead(cleanButtonPin) == LOW) {
                        delay(250);
                        break;
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
